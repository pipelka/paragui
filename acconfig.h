#ifndef GNU_CONFIG_INCLUDED
#define GNU_CONFIG_INCLUDED

@TOP@

/* Define if you the the SDL_image library (-lSDL_Image) */
#undef HAVE_SDLIMAGE

/* Define the default path to the theme files */
#define PARAGUI_THEMEDIR "./data"

/* Define if RTTI is enabled in your compiler (for dynamic_cast and typeid) */
#undef RTTI_ENABLED

/* Define if the exception handling is enabled in your compiler */
#undef EXCEPTIONS_ENABLED

/* Define if mpatrol memory profiler support is enabled */
#undef MPATROL_ENABLED

@BOTTOM@

#endif // GNU_CONFIG_INCLUDED
