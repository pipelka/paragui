noinst_LTLIBRARIES = libphysfs.la

if BUILD_ZLIB
ZLIB_DIR = zlib114
ZLIB_LIB = zlib114/libz.la
ZLIB_INC = -I./zlib114
else
ZLIB_LIB = -lz
ZLIB_INC =
endif

if BUILD_TEST_PHYSFS
TEST_DIR = . test
endif

SUBDIRS = archivers platform $(ZLIB_DIR) $(TEST_DIR)

DIST_SUBDIRS = $(SUBDIRS) extras zlib114 test

libphysfsincludedir = $(includedir)
libphysfsinclude_HEADERS =	\
	physfs.h

libphysfs_la_SOURCES =	\
	physfs.c \
	physfs_internal.h \
	physfs_byteorder.c

libphysfs_la_LIBADD = \
	archivers/libarchivers.la \
	platform/libplatform.la \
	$(ZLIB_LIB)

libphysfs_la_INCLUDES = $(ZLIB_INC)

libphysfs_la_LDFLAGS = 		\
	-release $(LT_RELEASE)	\
	-version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)

EXTRA_DIST = \
	CREDITS \
	LICENSE \
	CHANGELOG \
	INSTALL \
	TODO \
	Doxyfile \
	CWProjects.sit \
	physfs.dsp \
	test_physfs.dsp
