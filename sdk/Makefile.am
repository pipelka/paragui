EXTRA_DIST = \
	README.sampleapp \
	sampleapp.tar.gz

sampleapp.tar.gz:
	tar --exclude CVS -czvf sampleapp.tar.gz $(srcdir)/sampleapp

all: sampleapp.tar.gz
