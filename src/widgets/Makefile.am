noinst_LTLIBRARIES = libpgwidgets.la

libpgwidgets_la_SOURCES = \
pgbutton.cpp \
pgcheckbutton.cpp \
pgcolumnitem.cpp \
pgdropdown.cpp \
pgimage.cpp \
pglabel.cpp \
pglayout.cpp \
pglineedit.cpp \
pglistboxbaseitem.cpp \
pglistbox.cpp \
pglistboxitem.cpp \
pgmaskedit.cpp \
pgmessagebox.cpp \
pgpopupmenu.cpp \
pgprogressbar.cpp \
pgradiobutton.cpp \
pgrichedit.cpp \
pgscrollbar.cpp \
pgslider.cpp \
pgspinnerbox.cpp \
pgthemewidget.cpp \
pgwidget.cpp \
pgwidgetdnd.cpp \
pgwidgetlist.cpp \
pgwidgetlistex.cpp \
pgwindow.cpp \
pgmenubar.cpp
#pgbuttongroup.cpp \
#pgnotebook.cpp \

EXTRA_DIST =

INCLUDES = \
	$(EXPAT_INCLUDE) \
	$(SDL_CFLAGS) \
	-I$(top_srcdir)/include

style_cvs:
	astyle --style=kr --indent=tab=4 --indent-switches *.cpp

style_personal:
	astyle *.cpp
