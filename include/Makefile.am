libparaguiincludedir = $(includedir)/paragui

libparaguiinclude_HEADERS = \
	paraconfig.h \
	paraconfig_gnu.h \
	paragui.h \
	paragui_types.h \
	pgrect.h \
	pgrectlist.h \
	pgwidgetlist.h \
	pglabel.h \
	pgwidgetdnd.h \
	pgwidget.h \
	pgthemewidget.h \
	pgmessageobject.h \
	pgbutton.h \
	pgapplication.h \
	pgscrollbar.h \
	pgwindow.h \
	pglineedit.h \
	pgprogressbar.h \
	pgradiobutton.h \
	pgcheckbutton.h \
	pgslider.h \
	pgtheme.h \
	pglistboxbaseitem.h \
	pglistboxitem.h \
	pglistbox.h \
	pgcolumnitem.h \
	pgdropdown.h \
	pgsurfacecache.h \
	pgeventobject.h \
	pgpopupmenu.h \
	pgmessagebox.h \
	pgmaskedit.h \
	pgspinnerbox.h \
	pgnavigator.h \
	pgwidgetlistex.h \
	pgrichedit.h \
	pgimage.h \
	pglayout.h \
	pglog.h \
	pgfilearchive.h \
	pgfile.h \
	pgfont.h \
	pgcolors.h \
	pgdraw.h \
	pginfo.h \
	pgmenubar.h \
	pgcompat.h \
	pgdatacontainer.h \
	pgtimerobject.h

EXTRA_DIST = \
	paraconfig_win32.h \
	paraconfig_gnu.h.in

style_cvs:
	astyle --style=kr --indent=tab=4 --indent-switches *.h

style_personal:
	astyle *.h
