#ifndef WIN32_CONFIG_INCLUDED
#define WIN32_CONFIG_INCLUDED

#ifndef PARAGUI_DYNAMIC_EXPORTS
#undef DECLSPEC
#define DECLSPEC __declspec(dllimport)
#endif

#ifndef __MINGW32__
// disable some nerved non-critical warnings (for now)
#pragma warning(disable: 4275)
#pragma warning(disable: 4251)
#endif

/* Define if UNICODE support is enabled */
#define PG_ENABLE_UNICODE 1

/* Define if you want to include the builtin colortable */
#define PG_ENABLE_PGCOLORS 1

/* Define if you have the SDL_image library */
#define PG_HAVE_SDLIMAGE 1

/* Define the default path to the theme files */
#define PG_PARAGUI_THEMEDIR "./data"

/* Define if you have the fnmatch function.  */
/* #undef PG_HAVE_FNMATCH */

/* Define if you have the strdup function.  */
/* #undef PG_HAVE_STRDUP */

/* Define if you have the strtok function.  */
#define PG_HAVE_STRTOK 1

/* Define if you have the vsnprintf function.  */
/* #undef PG_HAVE_VSNPRINTF */

/* Define if you have the jpeg library (-ljpeg).  */
#define PG_HAVE_LIBJPEG 1

/* Define if you have the png library (-lpng).  */
#define PG_HAVE_LIBPNG 1

/* Define if you have the tiff library (-ltiff).  */
#define PG_HAVE_LIBTIFF 1

/* SDL_image shared library */
#define PG_SDLIMAGE_LIB "sdl_image.dll"

#ifdef _MSC_VER
#define PG_HAVE_STRDUP 1
#endif

// Some stuff needed for Win32
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <windows.h>
extern int SDL_RegisterApp(char*, Uint32, void*);
#undef SendMessage
#endif // WIN32

#endif // WIN32_CONFIG_INCLUDED
