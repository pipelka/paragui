noinst_PROGRAMS = keyboard

keyboard_SOURCES = \
	keyboard.cpp \
	main.cpp

keyboard_LDADD = $(SDL_LIBS) -L../../src ../../src/libparagui.la $(FREETYPE_LIBS)

EXTRA_DIST = \
	keyboard.h

INCLUDES = \
	-I$(top_srcdir)/include \
	$(PARAGUI_CFLAGS)
