noinst_PROGRAMS = colorselector

colorselector_SOURCES = \
	pgcolorselector.cpp \
	main.cpp

colorselector_LDADD = -L../../src ../../src/libparagui.la $(FREETYPE_LIBS)

EXTRA_DIST = \
	pgcolorselector.h

INCLUDES = \
	-I$(top_srcdir)/include \
	$(PARAGUI_CFLAGS)
