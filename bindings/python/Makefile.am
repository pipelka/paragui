SWIGCOMPILE = $(SWIG) -python -shadow -c++ -I$(top_srcdir)/include -I$(srcdir)

COMPILE = $(CC) $(CXXFLAGS) -fpic

PGHEADERS=$(shell ls $(top_srcdir)/include/*.h)

LINK = $(COMPILE) -shared \
	-L@prefix@/lib \
	-lexpat \
	-lz \
	$(SDL_LIBS) \
	$(IMAGE_LIBS) \
	$(LIBSTDCPP) \
	-lparagui -L$(top_srcdir)/src

INCLUDES = \
	$(SDL_CFLAGS) \
	-I$(top_srcdir)/include \
	-I$(PYTHON_INCLUDE_DIR) \
	-I../../include


OBJECTS = \
	paraguic_wrap.o

paraguicmodule.so: $(OBJECTS)
	$(LINK) $(OBJECTS) -o paraguicmodule.so

#paragui.py:

#paragui.pyc:
#	python -c "import paragui" 2>/dev/null || echo -n

#paragui.pyo:
#	python -OO -c "import paragui" 2>/dev/null || echo -n

paraguic_wrap.cpp: $(PGHEADERS) python.h
	$(SWIGCOMPILE) -I$(top_srcdir)/include -o paraguic_wrap.cpp python.h

paraguic_wrap.o: paraguic_wrap.cpp
	$(COMPILE) $(INCLUDES) -c $<

distclean: clean
	rm -f Makefile

clean:
	rm -f *.so *.c *.o *~ *. *.cpp *.py?

.PHONY: clean

parapythondir = $(PYTHON_LIB_DIR)

parapython_DATA = \
	paraguicmodule.so \
	paragui.py \
	paragui.pyc \
	paragui.pyo

EXTRA_DIST = \
	swigcommon.h \
	python.h
