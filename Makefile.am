AUTOMAKE_OPTIONS = 1.4

SUBDIRS = include src data bindings

DIST_SUBDIRS = $(SUBDIRS) doc test

bin_SCRIPTS = paragui-config

EXTRA_DIST = \
	paragui.m4 \
	paragui.spec.in \
	paragui.pc.in \
	README \
	README-ParaGUI.txt \
	COPYING \
	INSTALL \
	TODO \
	VisualC.zip \
	mkdist-beos.sh

m4datadir = $(datadir)/aclocal
m4data_DATA = paragui.m4

pkgconfigdir = $(prefix)/lib/pkgconfig
pkgconfig_DATA = paragui.pc

$(PACKAGE)-$(VERSION).tar.gz: dist

release:
	if test ! -f $(top_builddir)/test/Makefile; then \
	    mkdir -p $(top_builddir)/test ; \
	    cd $(top_builddir)/test ; ../$(srcdir)/test/configure --disable-paraguitest ; \
	fi
	rm -f $(top_builddir)/VisualC.zip
	rm -f $(top_builddir)/data/*.zip
	make dist

touch:
	touch `find`

clean:
	rm -f $(top_builddir)/VisualC.zip

VisualC.zip:
	mkdir -p $(top_builddir)/VC-build
	cp -rf $(top_srcdir)/VisualC $(top_builddir)/VC-build/VisualC
	dsw=`find $(top_builddir)/VC-build/VisualC -name "*.dsw"`; \
	dsp=`find $(top_builddir)/VC-build/VisualC -name "*.dsp"`; \
	mak=`find $(top_builddir)/VC-build/VisualC -name "*.mak"`; \
	for file in $$dsp $$dsw $$mak; do \
	    unix2dos $$file || echo "unix2dos not found!"; \
	done
	rm -f $(top_builddir)/VisualC.zip && cd $(top_builddir)/VC-build && zip -9 -r $(TOP_BUILDDIR)/VisualC.zip VisualC -i *.dsp *.dsw *.mak
	rm -Rf $(top_builddir)/VC-build

dist-hook:
	chmod +x $(srcdir)/mkdist-beos.sh
	mkdir $(distdir)/bin
	cp $(srcdir)/bin/README.txt $(distdir)/bin
	mkdir $(distdir)/lib
	cp $(srcdir)/lib/README.txt $(distdir)/lib
	rm -f $(distdir)/VisualC.zip
	cp -f $(top_builddir)/VisualC.zip $(distdir)
	rm -f $(distdir)/data/*.zip
	cp -f $(top_builddir)/data/*.zip $(distdir)/data

dist_bz2: $(PACKAGE)-$(VERSION).tar.gz
	gzip -c -d $(PACKAGE)-$(VERSION).tar.gz > $(PACKAGE)-$(VERSION).tar
	bzip2 $(PACKAGE)-$(VERSION).tar

install-hook:
	-ldconfig

rpm: $(PACKAGE)-$(VERSION).tar.gz
	cp $(PACKAGE)-$(VERSION).tar.gz $(RPM_ROOT)
	rpm -ba $(PACKAGE).spec

rpm_i686: $(PACKAGE)-$(VERSION).tar.gz 
	cp $(PACKAGE)-$(VERSION).tar.gz $(RPM_ROOT)
	rpm -ba --target=i686-linux $(PACKAGE).spec

rpm_i586: $(PACKAGE)-$(VERSION).tar.gz 
	cp $(PACKAGE)-$(VERSION).tar.gz $(RPM_ROOT)
	rpm -ba --target i586-linux $(PACKAGE).spec

rpm_i486: $(PACKAGE)-$(VERSION).tar.gz
	cp $(PACKAGE)-$(VERSION).tar.gz $(RPM_ROOT)
	rpm -ba --target=i486-linux $(PACKAGE).spec

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
