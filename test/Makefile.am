SUBDIRS = fireworks

AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = stress1 stress2 listbox animation dropdown paratest dblbuffer navtest windowtest layouttest windowresize

stress1_SOURCES = stress1.cpp
stress1_LDADD = -L../src $(PARAGUI_LIBS)

stress2_SOURCES = stress2.cpp
stress2_LDADD = -L../src $(PARAGUI_LIBS)

listbox_SOURCES = listbox.cpp
listbox_LDADD = -L../src $(PARAGUI_LIBS)

windowresize_SOURCES = windowresize.cpp
windowresize_LDADD = -L../src $(PARAGUI_LIBS)

dropdown_SOURCES = dropdown.cpp
dropdown_LDADD = -L../src $(PARAGUI_LIBS)

animation_SOURCES = animation.cpp
animation_LDADD = -L../src $(PARAGUI_LIBS)

dblbuffer_SOURCES = dblbuffer.cpp
dblbuffer_LDADD = -L../src $(PARAGUI_LIBS)

paratest_SOURCES = paratest.cpp
paratest_LDADD = -L../src $(PARAGUI_LIBS)

navtest_SOURCES = navtest.cpp
navtest_LDADD = -L../src $(PARAGUI_LIBS)

windowtest_SOURCES = windowtest.cpp
windowtest_LDADD = -L../src $(PARAGUI_LIBS)

layouttest_SOURCES = layouttest.cpp
layouttest_LDADD = -L../src $(PARAGUI_LIBS)

INCLUDES = $(PARAGUI_CFLAGS) -I$(top_srcdir)/include

$(PACKAGE)-$(VERSION).tar.gz: dist

EXTRA_DIST = \
	dblbuffer.xml \
	pokus.xml \
	icon.bmp

mlz: $(PACKAGE)-$(VERSION).tar.gz
	mkdir $(PACKAGE)-$(VERSION)
	cp $(PACKAGE)-$(VERSION).tar.gz $(PACKAGE)-$(VERSION)
	cp -rf mlz/* $(PACKAGE)-$(VERSION)
	rm -Rf $(PACKAGE)-$(VERSION)/CVS
	rm -Rf $(PACKAGE)-$(VERSION)/init.d/CVS
	tar -czvf $(PACKAGE)-$(VERSION)_ML1.0.0-beta3.mlz $(PACKAGE)-$(VERSION)
	rm -Rf $(PACKAGE)-$(VERSION)
