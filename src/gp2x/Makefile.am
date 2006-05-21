noinst_LTLIBRARIES = libpggp2x.la

libpggp2x_la_SOURCES = \
	gp2xapplication.cpp \
	gp2xevents.cpp

INCLUDES = \
	$(SDL_CFLAGS) \
	$(SIGC_CFLAGS) \
	-I$(top_srcdir)/include

style_cvs:
	astyle --style=kr --indent=tab=4 --indent-switches *.cpp

style_personal:
	astyle *.cpp
