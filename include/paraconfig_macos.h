#ifndef MACOS_CONFIG_INCLUDED
#define MACOS_CONFIG_INCLUDED

/* Define to 1 if UNICODE support is enabled */
/* #undef UNICODE_ENABLED */

/* Define if you the the SDL_image library (-lSDL_Image) */
#define PG_HAVE_SDLIMAGE 1

/* Define the default path to the theme files */
#define PG_PARAGUI_THEMEDIR ":data:"

/* Define if RTTI is enabled in your compiler (for dynamic_cast and typeid) */
#define PG_RTTI_ENABLED 1

/* Define if the exception handling is enabled in your compiler */
#undef PG_EXCEPTIONS_ENABLED

/* Define if mpatrol memory profiler support is enabled */
/* #undef PG_MPATROL_ENABLED */

/* Define if you have the fnmatch function.  */
/* #undef PG_HAVE_FNMATCH */

/* Define if you have the strdup function.  */
/* #undef PG_HAVE_STRDUP */

/* Define if you have the strtok function.  */
#define PG_HAVE_STRTOK 1

/* Define if you have the vsnprintf function.  */
#define PG_HAVE_VSNPRINTF 1

/* Define if you have the <dlfcn.h> header file.  */
#define PG_HAVE_DLFCN_H 1

/* Define if you have the jpeg library (-ljpeg).  */
#define PG_HAVE_LIBJPEG 1

/* Define if you have the png library (-lpng).  */
#define PG_HAVE_LIBPNG 1

/* Define if you have the tiff library (-ltiff).  */
#define PG_HAVE_LIBTIFF 1

/* SDL_image shared library */
#define PG_SDLIMAGE_LIB "???"

#endif
