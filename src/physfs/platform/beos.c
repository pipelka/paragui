/*
 * BeOS support routines for PhysicsFS.
 *
 * Please see the file LICENSE in the source's root directory.
 *
 *  Adapted for BeOS by Alexander Pipelka <pipelka@teleweb.at>
 *  based on unix.c written by Ryan C. Gordon.
 */

#include <be/kernel/OS.h>
#include <be/kernel/fs_info.h>
#include <be/kernel/fs_query.h>
#include <be/kernel/fs_index.h>

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <dirent.h>
#include <time.h>
#include <errno.h>

#include <dirent.h>

#define __PHYSICSFS_INTERNAL__
#include "physfs_internal.h"

const char *__PHYSFS_platformDirSeparator = "/";


int __PHYSFS_platformInit(void)
{
    return(1);  /* always succeed. */
} /* __PHYSFS_platformInit */


int __PHYSFS_platformDeinit(void)
{
    return(1);  /* always succeed. */
} /* __PHYSFS_platformDeinit */

// FIXME - needs to be implemented
char **__PHYSFS_platformDetectAvailableCDs(void)
{
    return NULL;
} /* __PHYSFS_platformDetectAvailableCDs */


char *__PHYSFS_platformCalcBaseDir(const char *argv0)
{
    /* If there isn't a path on argv0, then look through the $PATH for it. */

    char *retval = NULL;
    char *envr;
    char *start;
    char *ptr;
    char *exe;

    if (strchr(argv0, '/') != NULL)   /* default behaviour can handle this. */
        return(NULL);

    envr = copyEnvironmentVariable("PATH");
    BAIL_IF_MACRO(!envr, NULL, NULL);

    start = envr;
    do
    {
        ptr = strchr(start, ':');
        if (ptr)
            *ptr = '\0';

        exe = (char *) malloc(strlen(start) + strlen(argv0) + 2);
        if (!exe)
        {
            free(envr);
            BAIL_IF_MACRO(1, ERR_OUT_OF_MEMORY, NULL);
        } /* if */
        strcpy(exe, start);
        if (exe[strlen(exe) - 1] != '/')
            strcat(exe, "/");
        strcat(exe, argv0);
        if (access(exe, X_OK) != 0)
            free(exe);
        else
        {
            retval = exe;
            strcpy(retval, start);  /* i'm lazy. piss off. */
            break;
        } /* else */

        start = ptr + 1;
    } while (ptr != NULL);

    free(envr);
    return(retval);	
} /* __PHYSFS_platformCalcBaseDir */


static char *getUserNameByUID(void)
{
    uid_t uid = getuid();
    struct passwd *pw;
    char *retval = NULL;

    pw = getpwuid(uid);
    if ((pw != NULL) && (pw->pw_name != NULL))
    {
        retval = malloc(strlen(pw->pw_name) + 1);
        if (retval != NULL)
            strcpy(retval, pw->pw_name);
    } /* if */
    
    return(retval);
} /* getUserNameByUID */


char *__PHYSFS_platformGetUserName(void)
{
    char *retval = getUserNameByUID();
    if (retval == NULL)
        retval = copyEnvironmentVariable("USER");
    return(retval);	
} /* __PHYSFS_platformGetUserName */


static char *getUserDirByUID(void)
{
    uid_t uid = getuid();
    struct passwd *pw;
    char *retval = NULL;

    pw = getpwuid(uid);
    if ((pw != NULL) && (pw->pw_dir != NULL))
    {
        retval = malloc(strlen(pw->pw_dir) + 1);
        if (retval != NULL)
            strcpy(retval, pw->pw_dir);
    } /* if */
    
    return(retval);
} /* getUserDirByUID */


char *__PHYSFS_platformGetUserDir(void)
{
    char *retval = copyEnvironmentVariable("HOME");
    if (retval == NULL)
        retval = getUserDirByUID();
    return(retval);	
} /* __PHYSFS_platformGetUserDir */


PHYSFS_uint64 __PHYSFS_platformGetThreadID(void)
{
    return((PHYSFS_uint64)find_thread(NULL));	
} /* __PHYSFS_platformGetThreadID */


int __PHYSFS_platformStricmp(const char *x, const char *y)
{
    int ux, uy;

    do
    {
        ux = toupper((int) *x);
        uy = toupper((int) *y);
        if (ux > uy)
            return(1);
        else if (ux < uy)
            return(-1);
        x++;
        y++;
    } while ((ux) && (uy));

    return(0);	
} /* __PHYSFS_platformStricmp */


int __PHYSFS_platformExists(const char *fname)
{
    struct stat statbuf;
    return(stat(fname, &statbuf) == 0);	
} /* __PHYSFS_platformExists */


int __PHYSFS_platformIsSymLink(const char *fname)
{
#if (defined __PHYSFS_NO_SYMLINKS__)
    return(0);
#else

    struct stat statbuf;
    int retval = 0;

    if (lstat(fname, &statbuf) == 0)
    {
        if (S_ISLNK(statbuf.st_mode))
            retval = 1;
    } /* if */
    
    return(retval);

#endif	
} /* __PHYSFS_platformIsSymlink */


int __PHYSFS_platformIsDirectory(const char *fname)
{
    struct stat statbuf;
    int retval = 0;

    if (stat(fname, &statbuf) == 0)
    {
        if (S_ISDIR(statbuf.st_mode))
            retval = 1;
    } /* if */
    
    return(retval);	
} /* __PHYSFS_platformIsDirectory */


char *__PHYSFS_platformCvtToDependent(const char *prepend,
                                      const char *dirName,
                                      const char *append)
{
    int len = ((prepend) ? strlen(prepend) : 0) +
              ((append) ? strlen(append) : 0) +
              strlen(dirName) + 1;
    char *retval = malloc(len);

    BAIL_IF_MACRO(retval == NULL, ERR_OUT_OF_MEMORY, NULL);

    /* platform-independent notation is Unix-style already.  :)  */

    if (prepend)
        strcpy(retval, prepend);
    else
        retval[0] = '\0';

    strcat(retval, dirName);

    if (append)
        strcat(retval, append);

    return(retval);
} /* __PHYSFS_platformCvtToDependent */


void __PHYSFS_platformTimeslice(void)
{
	snooze(10);	
} /* __PHYSFS_platformTimeslice */


LinkedStringList *__PHYSFS_platformEnumerateFiles(const char *dirname,
                                                  int omitSymLinks)
{
    static char dev_query[255];
    dev_t device;
    LinkedStringList *retval = NULL;
    LinkedStringList *l = NULL;
    LinkedStringList *prev = NULL;
    DIR *dir;
    struct dirent *ent;
    int bufsize = 0;
    char *buf = NULL;
    int dlen = 0;

    if (omitSymLinks)
    {
        dlen = strlen(dirname);
        bufsize = dlen + 256;
        buf = malloc(bufsize);
        BAIL_IF_MACRO(buf == NULL, ERR_OUT_OF_MEMORY, NULL);
        strcpy(buf, dirname);
        if (buf[dlen - 1] != '/')
        {
            buf[dlen++] = '/';
            buf[dlen] = '\0';
        } /* if */
    } /* if */

    /* open the device */
    device = dev_for_path((const char*)dirname);
    
    /* open the query */
    sprintf(dev_query, "name=%s/*", dirname);
    dir = fs_open_query(device, dev_query, 0);   
    errno = 0;

    if (dir == NULL)
    {
        if (buf != NULL)
            free(buf);
        BAIL_IF_MACRO(1, strerror(errno), NULL);
    } /* if */

    while (1)
    {
        ent = fs_read_query(dir);
        if (ent == NULL)   /* we're done. */
            break;

        if (strcmp(ent->d_name, ".") == 0)
            continue;

        if (strcmp(ent->d_name, "..") == 0)
            continue;

        if (omitSymLinks)
        {
            char *p;
            int len = strlen(ent->d_name) + dlen + 1;
            if (len > bufsize)
            {
                p = realloc(buf, len);
                if (p == NULL)
                    continue;
                buf = p;
                bufsize = len;
            } /* if */

            strcpy(buf + dlen, ent->d_name);
            if (__PHYSFS_platformIsSymLink(buf))
                continue;
        } /* if */

        l = (LinkedStringList *) malloc(sizeof (LinkedStringList));
        if (l == NULL)
            break;

        l->str = (char *) malloc(strlen(ent->d_name) + 1);
        if (l->str == NULL)
        {
            free(l);
            break;
        } /* if */

        strcpy(l->str, ent->d_name);

        if (retval == NULL)
            retval = l;
        else
            prev->next = l;

        prev = l;
        l->next = NULL;
    } /* while */

    if (buf != NULL)
        free(buf);

    /* close the query */
    fs_close_query(dir);
    
    return(retval);	
} /* __PHYSFS_platformEnumerateFiles */


char *__PHYSFS_platformCurrentDir(void)
{
    int allocSize = 0;
    char *retval = NULL;
    char *ptr;

    do
    {
        allocSize += 100;
        ptr = (char *) realloc(retval, allocSize);
        if (ptr == NULL)
        {
            if (retval != NULL)
                free(retval);
            BAIL_IF_MACRO(1, ERR_OUT_OF_MEMORY, NULL);
        } /* if */
	
        retval = ptr;
        ptr = getcwd(retval, allocSize);
    } while (ptr == NULL && errno == ERANGE);
    if(ptr == NULL && errno) {
	/* getcwd() failed for some reason, for example current
	 * directory not existing.
	 */
	if (retval != NULL)
	    free(retval);
	BAIL_IF_MACRO(1, ERR_NO_SUCH_FILE, NULL);
    }
    return(retval);	
} /* __PHYSFS_platformCurrentDir */


char *__PHYSFS_platformRealPath(const char *path)
{
	// hmm,.. didn't solve this for BeOS till now
	// trying the easy route (FIXME)

    char *retval = malloc(strlen(path) + 1);
    strcpy(retval, path);

    return(retval);   	
} /* __PHYSFS_platformRealPath */


int __PHYSFS_platformMkDir(const char *path)
{
    int rc;
    errno = 0;
    rc = mkdir(path, S_IRWXU);
    BAIL_IF_MACRO(rc == -1, strerror(errno), 0);
    return(1);	
} /* __PHYSFS_platformMkDir */


static void *doOpen(const char *filename, const char *mode)
{
    FILE *retval;
    errno = 0;

    retval = fopen(filename, mode);
    if (retval == NULL)
        __PHYSFS_setError(strerror(errno));

    return((void *) retval);
} /* doOpen */


void *__PHYSFS_platformOpenRead(const char *filename)
{
    return(doOpen(filename, "rb"));
} /* __PHYSFS_platformOpenRead */


void *__PHYSFS_platformOpenWrite(const char *filename)
{
    return(doOpen(filename, "wb"));	
} /* __PHYSFS_platformOpenWrite */


void *__PHYSFS_platformOpenAppend(const char *filename)
{
    return(doOpen(filename, "wb+"));	
} /* __PHYSFS_platformOpenAppend */


PHYSFS_sint64 __PHYSFS_platformRead(void *opaque, void *buffer,
                                    PHYSFS_uint32 size, PHYSFS_uint32 count)
{
    FILE *io = (FILE *) opaque;
    int rc = fread(buffer, size, count, io);
    if (rc < count)
    {
        int err = errno;
        BAIL_IF_MACRO(ferror(io), strerror(err), rc);
        BAIL_MACRO(ERR_PAST_EOF, rc);
    } /* if */

    return(rc);	
} /* __PHYSFS_platformRead */


PHYSFS_sint64 __PHYSFS_platformWrite(void *opaque, const void *buffer,
                                     PHYSFS_uint32 size, PHYSFS_uint32 count)
{
    FILE *io = (FILE *) opaque;
    int rc = fwrite((void *) buffer, size, count, io);
    if (rc < count)
        __PHYSFS_setError(strerror(errno));

    return(rc);	
} /* __PHYSFS_platformWrite */


int __PHYSFS_platformSeek(void *opaque, PHYSFS_uint64 pos)
{
    FILE *io = (FILE *) opaque;

    /* !!! FIXME: Use llseek where available. */
    errno = 0;
    BAIL_IF_MACRO(fseek(io, pos, SEEK_SET) != 0, strerror(errno), 0);

    return(1);	
} /* __PHYSFS_platformSeek */


PHYSFS_sint64 __PHYSFS_platformTell(void *opaque)
{
    FILE *io = (FILE *) opaque;
    PHYSFS_sint64 retval = ftell(io);
    BAIL_IF_MACRO(retval == -1, strerror(errno), -1);
    return(retval);	
} /* __PHYSFS_platformTell */


PHYSFS_sint64 __PHYSFS_platformFileLength(void *opaque)
{
    FILE *io = (FILE *) opaque;
    struct stat statbuf;
    errno = 0;
    BAIL_IF_MACRO(fstat(fileno(io), &statbuf) == -1, strerror(errno), -1);
    return((PHYSFS_sint64) statbuf.st_size);	
} /* __PHYSFS_platformFileLength */


int __PHYSFS_platformEOF(void *opaque)
{
    return(feof((FILE *) opaque));	
} /* __PHYSFS_platformEOF */


int __PHYSFS_platformFlush(void *opaque)
{
    errno = 0;
    BAIL_IF_MACRO(fflush((FILE *) opaque) == EOF, strerror(errno), 0);
    return(1);	
} /* __PHYSFS_platformFlush */


int __PHYSFS_platformClose(void *opaque)
{
    errno = 0;
    BAIL_IF_MACRO(fclose((FILE *) opaque) == EOF, strerror(errno), 0);
    return(1);	
} /* __PHYSFS_platformClose */


int __PHYSFS_platformDelete(const char *path)
{
    errno = 0;
    BAIL_IF_MACRO(remove(path) == -1, strerror(errno), 0);
    return(1);	
} /* __PHYSFS_platformDelete */


void *__PHYSFS_platformCreateMutex(void)
{
    return((void *) 0x0001);	
} /* __PHYSFS_platformCreateMutex */


void __PHYSFS_platformDestroyMutex(void *mutex)
{
} /* __PHYSFS_platformDestroyMutex */


int __PHYSFS_platformGrabMutex(void *mutex)
{
	return(1);
} /* __PHYSFS_platformGrabMutex */


void __PHYSFS_platformReleaseMutex(void *mutex)
{
} /* __PHYSFS_platformReleaseMutex */

/* end of skeleton.c ... */

