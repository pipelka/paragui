AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = stress1 stress2 listbox animation dropdown paratest dblbuffer navtest windowtest layouttest windowresize

stress1_SOURCES = stress1.cpp
stress1_LDADD = $(PARAGUI_LIBS)

stress2_SOURCES = stress2.cpp
stress2_LDADD = $(PARAGUI_LIBS)

listbox_SOURCES = listbox.cpp
listbox_LDADD = $(PARAGUI_LIBS)

windowresize_SOURCES = windowresize.cpp
windowresize_LDADD = $(PARAGUI_LIBS)

dropdown_SOURCES = dropdown.cpp
dropdown_LDADD = $(PARAGUI_LIBS)

animation_SOURCES = animation.cpp
animation_LDADD = $(PARAGUI_LIBS)

dblbuffer_SOURCES = dblbuffer.cpp
dblbuffer_LDADD = $(PARAGUI_LIBS)

paratest_SOURCES = paratest.cpp
paratest_LDADD = $(PARAGUI_LIBS)

navtest_SOURCES = navtest.cpp
navtest_LDADD = $(PARAGUI_LIBS)

windowtest_SOURCES = windowtest.cpp
windowtest_LDADD = $(PARAGUI_LIBS)

layouttest_SOURCES = layouttest.cpp
layouttest_LDADD = $(PARAGUI_LIBS)

INCLUDES = $(PARAGUI_CFLAGS)

$(PACKAGE)-$(VERSION).tar.gz: dist

EXTRA_DIST = \
	dblbuffer.xml \
	pokus.xml \
	icon.bmp

dist-hook:
	rm -rf `find $(distdir) -type d -name CVS -print`

rpm: $(PACKAGE)-$(VERSION).tar.gz
	cp $(PACKAGE)-$(VERSION).tar.gz /usr/src/redhat/SOURCES
	rpm -ba $(PACKAGE).spec

mlz: $(PACKAGE)-$(VERSION).tar.gz
	mkdir $(PACKAGE)-$(VERSION)
	cp $(PACKAGE)-$(VERSION).tar.gz $(PACKAGE)-$(VERSION)
	cp -rf mlz/* $(PACKAGE)-$(VERSION)
	rm -Rf $(PACKAGE)-$(VERSION)/CVS
	rm -Rf $(PACKAGE)-$(VERSION)/init.d/CVS
	tar -czvf $(PACKAGE)-$(VERSION)_ML1.0.0-beta3.mlz $(PACKAGE)-$(VERSION)
	rm -Rf $(PACKAGE)-$(VERSION)
