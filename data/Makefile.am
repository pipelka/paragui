
BUILDDIR=@TOP_BUILDDIR@/data/

default.zip:
	(cd $(srcdir); zip -9 -r $(BUILDDIR)default.zip default.theme ./default/* -i *.png *.bmp *.ttf *.theme)

qnx.zip:
	(cd $(srcdir);zip -9 -r $(BUILDDIR)qnx.zip qnx.theme qnx -i *.png *.bmp *.ttf *.theme)

simple.zip:
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
