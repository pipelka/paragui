X = adler32.c		\
	compress.c		\
	crc32.c			\
	deflate.c		\
	deflate.h		\
	infblock.c		\
	infblock.h		\
	infcodes.c		\
	infcodes.h		\
	inffast.c		\
	inffast.h		\
	inffixed.h		\
	inflate.c		\
	inftrees.c		\
	inftrees.h		\
	infutil.c		\
	infutil.h		\
	trees.c			\
	trees.h			\
	uncompr.c		\
	zconf.h			\
	zlib.h			\
	zutil.c			\
	zutil.h

if BUILD_ZLIB
  noinst_LTLIBRARIES = libz.la
  libz_la_SOURCES = $(X)
else
  EXTRA_DIST = $(X)
endif

