SUBDIRS = physfs draw font themes core widgets

lib_LTLIBRARIES = libparagui.la

EXTRA_DIST =

libparagui_la_SOURCES = \
	paragui.cpp

libparagui_la_LDFLAGS = \
	-release $(LT_RELEASE) \
	-version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)

libparagui_la_LIBADD = \
	-L@prefix@/lib \
	./physfs/libphysfs.la \
	./draw/libpgdraw.la \
	./font/libpgfont.la \
	./core/libpgcore.la \
	./widgets/libpgwidgets.la \
	./themes/libtheme.la \
	-lexpat \
	-lz \
	$(SDL_LIBS) \
	$(IMAGE_LIBS) \
	$(LIBSTDCPP)

INCLUDES = \
	$(SDL_CFLAGS) \
	-I$(top_srcdir)/include

style_cvs:
	astyle --style=kr --indent=tab=4 --indent-switches *.cpp

style_personal:
	astyle *.cpp
