noinst_PROGRAMS = fireworks

fireworks_SOURCES = \
	blob.cpp \
	main.cpp

fireworks_LDADD = \
	$(SDL_LIBS) \
	-L../../src ../../src/libparagui.la \
	$(FREETYPE_LIBS) \
	$(LIBSTDCPP)

EXTRA_DIST = \
	blob.h

INCLUDES = \
	-I$(top_srcdir)/include \
	$(SDL_CFLAGS) \
	$(SIGC_CFLAGS)
