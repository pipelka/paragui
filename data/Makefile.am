
BUILDDIR=@TOP_BUILDDIR@/data/

default.zip:
	chmod -R 644 $(srcdir)/default/*.*
	chmod -R 644 $(srcdir)/default.theme
	chmod 755 $(srcdir)/default
	(cd $(srcdir); zip -9 -r $(BUILDDIR)default.zip default.theme ./default/* -i *.png *.bmp *.ttf *.theme)

qnx.zip:
	chmod -R 644 $(srcdir)qnx/*.*
	chmod -R 644 $(srcdir)/qnx.theme
	chmod 755 $(srcdir)/qnx
	(cd $(srcdir);zip -9 -r $(BUILDDIR)qnx.zip qnx.theme qnx -i *.png *.bmp *.ttf *.theme)

simple.zip:
	chmod -R 644 $(srcdir)/simple/*.*
	chmod -R 644 $(srcdir)/simple.theme
	chmod 755 $(srcdir)/simple
	(cd $(srcdir); zip -9 -r $(BUILDDIR)simple.zip simple.theme simple -i *.png *.bmp *.ttf *.theme)

default_mac.zip:
	(cd $(srcdir); zip -9 -r $(BUILDDIR)default_mac.zip default_mac.theme default -i *.png *.bmp *.theme)


paraguidatadir = $(datadir)/paragui

paraguidata_DATA = \
	default.zip \
	simple.zip
#	qnx.zip 

EXTRA_DIST = \
	default.zip \
	simple.zip
#	qnx.zip

clean:

distclean: clean
	rm -f Makefile
