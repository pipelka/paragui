AUTOMAKE_OPTIONS = foreign

SUBDIRS = \
	keyboard \
	fireworks \
	colorselector

noinst_PROGRAMS = \
	factory \
	eventleavebug \
	sigc \
	widgetlistbug \
	eventbug \
	array \
	writefile \
	stress1 \
	stress2 \
	listbox \
	animation \
	dropdown \
	paratest \
	dblbuffer \
	navtest \
	windowtest \
	layouttest \
	windowresize \
	unicodetest

LFLAGS=$(SDL_LIBS) -L../src ../src/libparagui.la $(FREETYPE_LIBS)

unicodetest_SOURCES = unicodetest.cpp
unicodetest_LDADD = $(LFLAGS)

factory_SOURCES = factory.cpp
factory_LDADD = $(LFLAGS) 

eventleavebug_SOURCES = eventleavebug.cpp
eventleavebug_LDADD = $(LFLAGS) 

sigc_SOURCES = sigc.cpp
sigc_LDADD = $(LFLAGS) 

widgetlistbug_SOURCES = widgetlistbug.cpp
widgetlistbug_LDADD = $(LFLAGS) 

eventbug_SOURCES = event_bug.cpp
eventbug_LDADD = $(LFLAGS)

array_SOURCES = array.cpp
array_LDADD = $(LFLAGS)

writefile_SOURCES = writefile.cpp
writefile_LDADD = $(LFLAGS)

stress1_SOURCES = stress1.cpp
stress1_LDADD = $(LFLAGS)

stress2_SOURCES = stress2.cpp
stress2_LDADD = $(LFLAGS)

listbox_SOURCES = listbox.cpp
listbox_LDADD = $(LFLAGS)

windowresize_SOURCES = windowresize.cpp
windowresize_LDADD = $(LFLAGS)

dropdown_SOURCES = dropdown.cpp
dropdown_LDADD = $(LFLAGS)

animation_SOURCES = animation.cpp
animation_LDADD = $(LFLAGS)

dblbuffer_SOURCES = dblbuffer.cpp
dblbuffer_LDADD = $(LFLAGS)

paratest_SOURCES = paratest.cpp
paratest_LDADD = $(LFLAGS)

navtest_SOURCES = navtest.cpp
navtest_LDADD = $(LFLAGS)

windowtest_SOURCES = windowtest.cpp
windowtest_LDADD = $(LFLAGS)

layouttest_SOURCES = layouttest.cpp
layouttest_LDADD = $(LFLAGS)

INCLUDES = $(PARAGUI_CFLAGS) -I$(top_srcdir)/include

$(PACKAGE)-$(VERSION).tar.gz: dist

EXTRA_DIST = \
	dblbuffer.xml \
	pokus.xml \
	icon.bmp \
	paratest.dev
