noinst_LTLIBRARIES = libplatform.la

if BUILD_BEOS_CPP
libplatform_la_SOURCES = \
	posix.c \
	beos.cpp
else
libplatform_la_SOURCES = \
	posix.c \
	unix.c
endif

EXTRA_DIST = \
	posix.c \
	unix.c \
	skeleton.c \
	win32.c \
	macclassic.c \
	beos.cpp
