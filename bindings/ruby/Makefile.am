SWIG = swig
SWIGCOMPILE = $(SWIG) -ruby -c++ -I$(top_srcdir)/include -I$(srcdir)

SWIGINTERFACE=interface.i

COMPILE = $(CC) $(CXXFLAGS) -fpic

PGHEADERS=$(shell ls $(top_srcdir)/include/*.h)

LINK = $(COMPILE) -shared \
	-L@prefix@/lib \
	-L$(top_srcdir)/src \
	$(PARAGUI_LIBS)

INCLUDES = \
	$(SDL_CFLAGS) \
	-I$(top_srcdir)/include \
	-I$(RUBY_INCLUDE_DIR) \
	-I../../include


OBJECTS = \
	paraguic_wrap.o

paragui.so: $(OBJECTS)
	$(LINK) $(OBJECTS) -o paragui.so

paraguic_wrap.cpp: $(PGHEADERS)
	$(SWIGCOMPILE) -o paraguic_wrap.cpp interface.i

paraguic_wrap.o: paraguic_wrap.cpp
	$(COMPILE) $(INCLUDES) -c $<

distclean: clean
	rm -f Makefile

clean:
	rm -f *.so *.c *.o *~ *. *.cpp

.PHONY: clean

pararubydir = $(RUBY_INSTALL_DIR)

pararuby_DATA = \
	paragui.so

EXTRA_DIST = \
	swigcommon.h \
	interface.i \
	dropdown.rb \
	layouttest.rb \
	listbox.rb \
	windowresize.rb \
	windowtest.rb \
	icon.bmp \
	pokus.xml
