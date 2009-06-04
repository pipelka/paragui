SUBDIRS = $(PHYSFS_SUBDIR) $(EXPAT_SUBDIR) draw font themes core widgets ystring gp2x

DIST_SUBDIRS = draw font themes core widgets expat physfs ystring gp2x

lib_LTLIBRARIES = libparagui.la

libparagui_la_SOURCES = paragui.cpp

libparagui_la_LDFLAGS = \
	-release $(LT_RELEASE) \
	-version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)

libparagui_la_LIBADD = \
	$(SIGC_LIBS) \
	$(SDL_LIBS) \
	$(EXPAT_LIB) \
	$(PHYSFS_LIB) \
	./draw/libpgdraw.la \
	./font/libpgfont.la \
	./core/libpgcore.la \
	./widgets/libpgwidgets.la \
	./themes/libtheme.la \
	./ystring/libystring.la \
	./gp2x/libpggp2x.la \
	$(VNCSERVER_LIBS) \
	$(LIBSTDCPP)

INCLUDES = \
	$(SIGC_CFLAGS) \
	$(SDL_CFLAGS) \
	-I$(top_srcdir)/include

style_cvs:
	dirs="draw font themes core widgets" ; for dir in $(SUBDIRS) ; do cd $$dir && make style_cvs && cd .. ; done
	astyle --style=kr --indent=tab=4 --indent-switches *.cpp

style_personal:
	astyle *.cpp
