AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = tabbar animation dropdown paratest dblbuffer navtest windowtest layouttest windowresize

tabbar_SOURCES = tabbar.cpp
tabbar_LDADD = ../src/libparagui.la -lfreetype

windowresize_SOURCES = windowresize.cpp
windowresize_LDADD = ../src/libparagui.la -lfreetype

dropdown_SOURCES = dropdown.cpp
dropdown_LDADD = ../src/libparagui.la -lfreetype

animation_SOURCES = animation.cpp
animation_LDADD = ../src/libparagui.la -lfreetype

dblbuffer_SOURCES = dblbuffer.cpp
dblbuffer_LDADD = ../src/libparagui.la -lfreetype

paratest_SOURCES = paratest.cpp
paratest_LDADD = ../src/libparagui.la -lfreetype

navtest_SOURCES = navtest.cpp
navtest_LDADD = ../src/libparagui.la -lfreetype

windowtest_SOURCES = windowtest.cpp
windowtest_LDADD = ../src/libparagui.la -lfreetype

layouttest_SOURCES = layouttest.cpp
layouttest_LDADD = ../src/libparagui.la -lfreetype

INCLUDES = \
	$(SDL_CFLAGS) \
	$(SIGC_CFLAGS) \
	$(EXPAT_INCLUDE) \
	$(FREETYPE_CFLAGS) \
	../include

$(PACKAGE)-$(VERSION).tar.gz: dist

EXTRA_DIST = \
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
