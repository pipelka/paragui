noinst_PROGRAMS = colorselector

colorselector_SOURCES = \
	pgcolorselector.cpp \
	main.cpp

colorselector_LDADD = \
	$(SDL_LIBS) \
	-L../../src ../../src/libparagui.la \
	$(FREETYPE_LIBS) \
	$(LIBSTDCPP) \
	$(SIGC_LIBS)

EXTRA_DIST = \
	pgcolorselector.h

INCLUDES = \
	-I$(top_srcdir)/include \
	$(SDL_CFLAGS) \
	$(SIGC_CFLAGS)
