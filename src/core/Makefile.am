noinst_LTLIBRARIES = libpgcore.la

libpgcore_la_SOURCES = \
	physfsrwops.cpp \
	missing.cpp \
	pgdatacontainer.cpp \
	pgapplication.cpp \
	pgcolors.cpp \
	pgeventobject.cpp \
	pgfilearchive.cpp \
	pgfile.cpp \
	pglog.cpp \
	pgmain.cpp \
	pgmessageobject.cpp \
	pgmsgmap.cpp \
	pgnavigator.cpp \
	pgrectlist.cpp \
	pgsurfacecache.cpp \
	pgtimerobject.cpp

libpgcore_la_LIBADD = 

EXTRA_DIST = \
	physfsrwops.h \
	pgmsgmap.h

INCLUDES = \
	$(SDL_CFLAGS) \
	$(PHYSFS_INCLUDE) \
	-I$(top_srcdir)/include

style_cvs:
	astyle --style=kr --indent=tab=4 --indent-switches *.cpp

style_personal:
	astyle *.cpp
