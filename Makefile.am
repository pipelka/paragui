DISTCHECK_CONFIGURE_FLAGS=--enable-internalexpat --enable-internalphysfs

SUBDIRS = include src data bindings

DIST_SUBDIRS = $(SUBDIRS) sdk doc test

bin_SCRIPTS = paragui-config

EXTRA_DIST = \
	paragui.m4 \
	paragui.spec.in \
	paragui.pc.in \
	paragui.dev \
	README \
	README-ParaGUI.txt \
	COPYING \
	INSTALL \
	TODO \
	VisualC.zip \
	mkdist-beos.sh \
	CWparagui.txt \
	CWProject.zip \
	depcomp


depcomp:
	touch depcomp

m4datadir = $(datadir)/aclocal
m4data_DATA = paragui.m4

pkgconfigdir = $(prefix)/lib/pkgconfig
pkgconfig_DATA = paragui.pc

$(PACKAGE)-$(VERSION).tar.gz: dist

release:
	rm -f $(top_builddir)/VisualC.zip
	rm -f $(top_builddir)/data/*.zip
	rm -f $(top_builddir)/sdk/*.tar.gz
	make dist

touch:
	touch `find`

VisualC.zip:
	mkdir -p $(top_builddir)/VC-build
	cp -rf $(top_srcdir)/VisualC $(top_builddir)/VC-build/VisualC
	dsw=`find $(top_builddir)/VC-build/VisualC -name "*.dsw"`; \
	dsp=`find $(top_builddir)/VC-build/VisualC -name "*.dsp"`; \
	mak=`find $(top_builddir)/VC-build/VisualC -name "*.mak"`; \
	for file in $$dsp $$dsw $$mak $$rc $$h $(top_builddir)/VC-build/VisualC/paragui_dynamic/resource.h $(top_builddir)/VC-build/VisualC/paragui_dynamic/Version.rc; do \
	    unix2dos $$file || echo "unix2dos not found!"; \
	done
	rm -f $(top_builddir)/VisualC.zip && cd $(top_builddir)/VC-build && zip -9 -r $(TOP_BUILDDIR)/VisualC.zip VisualC -i *.dsp *.dsw *.mak *.rc *.h
	rm -Rf $(top_builddir)/VC-build

dist-hook:
	chmod +x $(srcdir)/mkdist-beos.sh
	mkdir $(distdir)/bin
	cp $(srcdir)/bin/README.txt $(distdir)/bin
	mkdir $(distdir)/lib
	cp $(srcdir)/lib/README.txt $(distdir)/lib

install-hook:
	-ldconfig

rpm: $(PACKAGE)-$(VERSION).tar.gz
	cp $(PACKAGE)-$(VERSION).tar.gz $(RPM_ROOT)
	rpm -ba $(PACKAGE).spec

dist-beos: 
	export CFLAGS="-O2 -march=pentium"
	make
	make install
	cp $(top_builddir)/src/.libs/libparagui.so /boot/home/config/lib/
	cd $(top_builddir)/test ; make distclean || ./autogen.sh
	sh $(top_builddir)/mkdist-beos.sh 


style_cvs:
	cd $(top_srcdir)/src && make style_cvs
	cd $(top_srcdir)/include && make style_cvs

style_personal:
	cd $(top_srcdir)/src && make style_personal
	cd $(top_srcdir)include && make style_personal

mlz: $(PACKAGE)-$(VERSION).tar.gz
	mkdir $(PACKAGE)-$(VERSION)
	cp $(PACKAGE)-$(VERSION).tar.gz $(PACKAGE)-$(VERSION)
	cp -Rf $(top_srcdir)/mlz/* $(PACKAGE)-$(VERSION)
	rm -Rf $(PACKAGE)-$(VERSION)/CVS
	tar -czvf $(PACKAGE)-$(VERSION)_ML1.0.0-beta3.mlz $(PACKAGE)-$(VERSION)
	rm -Rf $(PACKAGE)-$(VERSION)
