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

$(PACKAGE)doc-html-$(VERSION).tar.gz: builddoc
	mkdir -p $(PACKAGE)doc-html-$(VERSION) ; \
	mkdir -p $(PACKAGE)doc-html-$(VERSION)/images ; \
	cp html/*.html $(PACKAGE)doc-html-$(VERSION) ; \
	cp html/*.gif $(PACKAGE)doc-html-$(VERSION); \
	cp html/*.map $(PACKAGE)doc-html-$(VERSION); \
	cp html/*.css $(PACKAGE)doc-html-$(VERSION); \
	cp html/*.png $(PACKAGE)doc-html-$(VERSION); \
	cp html/images/*.png $(PACKAGE)doc-html-$(VERSION)/images; \
	tar -zcf $(PACKAGE)doc-html-$(VERSION).tar.gz $(PACKAGE)doc-html-$(VERSION); \
	rm -Rf $(PACKAGE)doc-html-$(VERSION)

htmldoc: $(PACKAGE)doc-html-$(VERSION).tar.gz
