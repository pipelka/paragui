noinst_LTLIBRARIES=libexpat.la

libexpat_la_SOURCES = \
	xmltok.c \
	xmlrole.c \
	xmlparse.c

#INCLUDES = -DXML_NS -DXML_DTD -DXML_MIN_SIZE
INCLUDES = -DXML_MIN_SIZE

EXTRA_DIST = \
	expat.h \
	ascii.h \
	iasciitab.h \
	nametab.h \
	xmldef.h \
	xmlrole.h \
	xmltok.h \
	asciitab.h \
	latin1tab.h \
	utf8tab.h \
	xmlparse.h \
	xmltchar.h \
	xmltok_impl.h \
	xmltok_impl.c \
	xmltok_ns.c

# If you know what your system's byte order is, define XML_BYTE_ORDER:
# use -DXML_BYTE_ORDER=12 for little-endian byte order;
# use -DXML_BYTE_ORDER=21 for big-endian (network) byte order.
# -DXML_NS adds support for checking of lexical aspects of XML namespaces spec
# -DXML_MIN_SIZE makes a smaller but slower parser
# -DXML_DTD adds full support for parsing DTDs
