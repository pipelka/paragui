SUBDIRS = archivers platform

noinst_LTLIBRARIES = libphysfs.la

platform.c: $(srcdir)/$(PHYSFS_PLATFORMFILE)
	cp -f $(srcdir)/$(PHYSFS_PLATFORMFILE) platform.c

libphysfs_la_SOURCES = \
	physfs.c \
	physfs_byteorder.c \
	platform.c

libphysfs_la_LIBADD = ./archivers/libarchivers.la

EXTRA_DIST = \
	physfs.h \
	physfs_internal.h \
	CHANGELOG \
	INSTALL \
	LICENSE \
	TODO

INCLUDES = -DPHYSFS_SUPPORTS_ZIP

clean:
	rm -f platform.c
