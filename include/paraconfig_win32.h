#ifndef WIN32_CONFIG_INCLUDED
#define WIN32_CONFIG_INCLUDED

#ifndef __MINGW32__
// disable win32 warnings on exporting STL objects
#pragma warning(disable: 4275)
#pragma warning(disable: 4251)
#pragma warning(disable: 4786)
#pragma warning(disable: 4800)
#pragma warning(disable: 4091)
#pragma warning(disable: 4273)
#pragma warning(disable: 4806)

// strange thing but it works
#define PATH_MAX MAX_PATH
#endif

/* Define if UNICODE support is enabled */
//#define ENABLE_UNICODE

/* Define if you have the SDL_image library */
#define HAVE_SDLIMAGE 1

/* Define the default path to the theme files */
#define PARAGUI_THEMEDIR "./data"

/* Define if you have the fnmatch function.  */
/* #undef HAVE_FNMATCH */

/* Define if you have the strdup function.  */
/* #undef HAVE_STRDUP */

/* Define if you have the strtok function.  */
#define HAVE_STRTOK 1

/* Define if you have the vsnprintf function.  */
/* #undef HAVE_VSNPRINTF */

/* Define if you have the <ext/hash_map> header file.  */
/* #undef HAVE_EXT_HASH_MAP */

/* Define if you have the <hash_map> header file.  */
/* #undef HAVE_HASH_MAP */

/* Define if you have the jpeg library (-ljpeg).  */
#define HAVE_LIBJPEG 1

/* Define if you have the png library (-lpng).  */
#define HAVE_LIBPNG 1

/* Define if you have the tiff library (-ltiff).  */
#define HAVE_LIBTIFF 1

/* SDL_image shared library */
#define SDLIMAGE_LIB "sdl_image.dll"

/* Name of package */
#define PACKAGE "paragui"

/* Version number of package */
#define VERSION "1.1.8"

// Some stuff needed for Win32
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <windows.h>
extern int SDL_RegisterApp(char*, Uint32, void*);
#undef SendMessage
#endif // WIN32

#endif // WIN32_CONFIG_INCLUDED
