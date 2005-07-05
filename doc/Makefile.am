SUBDIRS = \
	html \
	txt

EXTRA_DIST = \
	paragui-config.sgml \
	RELEASENOTES \
	COPYRIGHT-FONTS.TXT \
	VisualC.html \
	TODO

builddoc: paragui.doxy
	doxygen paragui.doxy

html/index.html: builddoc

xml/index.xml: builddoc

$(PACKAGE)doc-html-$(VERSION).tar.gz: html/index.html paragui.devhelp.gz
	mkdir -p $(PACKAGE)doc-html-$(VERSION) ; \
	mkdir -p $(PACKAGE)doc-html-$(VERSION)/images ; \
	cp html/*.html $(PACKAGE)doc-html-$(VERSION) ; \
	cp html/*.gif $(PACKAGE)doc-html-$(VERSION); \
	cp html/*.map $(PACKAGE)doc-html-$(VERSION); \
	cp html/*.css $(PACKAGE)doc-html-$(VERSION); \
	cp html/*.png $(PACKAGE)doc-html-$(VERSION); \
	cp paragui.devhelp.gz $(PACKAGE)doc-html-$(VERSION); \
	cp html/images/*.png $(PACKAGE)doc-html-$(VERSION)/images; \
	tar -zcf $(PACKAGE)doc-html-$(VERSION).tar.gz $(PACKAGE)doc-html-$(VERSION); \
	rm -Rf $(PACKAGE)doc-html-$(VERSION)

htmldoc: $(PACKAGE)doc-html-$(VERSION).tar.gz

devhelp_file = paragui.devhelp

paragui.devhelp.gz: paragui.devhelp
	gzip -c -9 paragui.devhelp > paragui.devhelp.gz

paragui.devhelp: xml/index.xml
	xsltproc -o $(devhelp_file) doxygen_to_devhelp.xsl xml/index.xml

devhelpdir = $(prefix)/share/devhelp/books/paragui

install-devhelp: paragui.devhelp.gz html/index.html
	mkdir -p $(DESTDIR)$(devhelpdir)
	mkdir -p $(DESTDIR)$(devhelpdir)/images
	$(INSTALL_DATA) html/*.html $(DESTDIR)$(devhelpdir)
	$(INSTALL_DATA) html/*.gif $(DESTDIR)$(devhelpdir)
	$(INSTALL_DATA) html/*.map $(DESTDIR)$(devhelpdir)
	$(INSTALL_DATA) html/*.css $(DESTDIR)$(devhelpdir)
	$(INSTALL_DATA) html/*.png $(DESTDIR)$(devhelpdir)
	$(INSTALL_DATA) paragui.devhelp.gz $(DESTDIR)$(devhelpdir)
	$(INSTALL_DATA) html/images/*.png $(DESTDIR)$(devhelpdir)/images
