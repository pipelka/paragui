# Microsoft Developer Studio Generated NMAKE File, Based on paragui_static.dsp
!IF "$(CFG)" == ""
CFG=paragui_static - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. paragui_static - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "paragui_static - Win32 Release" && "$(CFG)" != "paragui_static - Win32 Debug" && "$(CFG)" != "paragui_static - Win32 Release MT" && "$(CFG)" != "paragui_static - Win32 Debug MT"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "paragui_static.mak" CFG="paragui_static - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "paragui_static - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "paragui_static - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "paragui_static - Win32 Release MT" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "paragui_static - Win32 Debug MT" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "paragui_static - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\..\lib\paraguis.lib"


CLEAN :
	-@erase "$(INTDIR)\dir.obj"
	-@erase "$(INTDIR)\drawline.obj"
	-@erase "$(INTDIR)\drawtile.obj"
	-@erase "$(INTDIR)\gradient.obj"
	-@erase "$(INTDIR)\missing.obj"
	-@erase "$(INTDIR)\paragui.obj"
	-@erase "$(INTDIR)\pgapplication.obj"
	-@erase "$(INTDIR)\pgbutton.obj"
	-@erase "$(INTDIR)\pgbuttongroup.obj"
	-@erase "$(INTDIR)\pgcheckbutton.obj"
	-@erase "$(INTDIR)\pgcolors.obj"
	-@erase "$(INTDIR)\pgcolumnitem.obj"
	-@erase "$(INTDIR)\pgdatacontainer.obj"
	-@erase "$(INTDIR)\pgdropdown.obj"
	-@erase "$(INTDIR)\pgeventobject.obj"
	-@erase "$(INTDIR)\pgfile.obj"
	-@erase "$(INTDIR)\pgfilearchive.obj"
	-@erase "$(INTDIR)\pgfont.obj"
	-@erase "$(INTDIR)\pgfont_impl.obj"
	-@erase "$(INTDIR)\pgimage.obj"
	-@erase "$(INTDIR)\pglabel.obj"
	-@erase "$(INTDIR)\pglayout.obj"
	-@erase "$(INTDIR)\pglineedit.obj"
	-@erase "$(INTDIR)\pglistbox.obj"
	-@erase "$(INTDIR)\pglistboxbaseitem.obj"
	-@erase "$(INTDIR)\pglistboxitem.obj"
	-@erase "$(INTDIR)\pglog.obj"
	-@erase "$(INTDIR)\pgmain.obj"
	-@erase "$(INTDIR)\pgmaskedit.obj"
	-@erase "$(INTDIR)\pgmenubar.obj"
	-@erase "$(INTDIR)\pgmessagebox.obj"
	-@erase "$(INTDIR)\pgmessageobject.obj"
	-@erase "$(INTDIR)\pgmsgmap.obj"
	-@erase "$(INTDIR)\pgnavigator.obj"
	-@erase "$(INTDIR)\pgpopupmenu.obj"
	-@erase "$(INTDIR)\pgprogressbar.obj"
	-@erase "$(INTDIR)\pgradiobutton.obj"
	-@erase "$(INTDIR)\pgrect.obj"
	-@erase "$(INTDIR)\pgrectlist.obj"
	-@erase "$(INTDIR)\pgrichedit.obj"
	-@erase "$(INTDIR)\pgscrollbar.obj"
	-@erase "$(INTDIR)\pgslider.obj"
	-@erase "$(INTDIR)\pgspinnerbox.obj"
	-@erase "$(INTDIR)\pgsurfacecache.obj"
	-@erase "$(INTDIR)\pgthemewidget.obj"
	-@erase "$(INTDIR)\pgwidget.obj"
	-@erase "$(INTDIR)\pgwidgetdnd.obj"
	-@erase "$(INTDIR)\pgwidgetlist.obj"
	-@erase "$(INTDIR)\pgwidgetlistex.obj"
	-@erase "$(INTDIR)\pgwindow.obj"
	-@erase "$(INTDIR)\physfs.obj"
	-@erase "$(INTDIR)\rotozoom.obj"
	-@erase "$(INTDIR)\setpixel.obj"
	-@erase "$(INTDIR)\stretch.obj"
	-@erase "$(INTDIR)\surface.obj"
	-@erase "$(INTDIR)\unzip.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\win32.obj"
	-@erase "$(INTDIR)\zip.obj"
	-@erase "..\..\lib\paraguis.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /vmg /GX /O2 /I "../../src/physfs" /I "../../src/themes" /I "../../src" /I "../../include" /D "HAVE_SDLIMAGE" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "PHYSFS_SUPPORTS_ZIP" /Fp"$(INTDIR)\paragui_static.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\paragui_static.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"../../lib/paraguis.lib" 
LIB32_OBJS= \
	"$(INTDIR)\missing.obj" \
	"$(INTDIR)\pgapplication.obj" \
	"$(INTDIR)\pgcolors.obj" \
	"$(INTDIR)\pgdatacontainer.obj" \
	"$(INTDIR)\pgeventobject.obj" \
	"$(INTDIR)\pgfile.obj" \
	"$(INTDIR)\pgfilearchive.obj" \
	"$(INTDIR)\pglog.obj" \
	"$(INTDIR)\pgmain.obj" \
	"$(INTDIR)\pgmessageobject.obj" \
	"$(INTDIR)\pgmsgmap.obj" \
	"$(INTDIR)\pgnavigator.obj" \
	"$(INTDIR)\pgrectlist.obj" \
	"$(INTDIR)\pgsurfacecache.obj" \
	"$(INTDIR)\pgfont.obj" \
	"$(INTDIR)\pgfont_impl.obj" \
	"$(INTDIR)\drawline.obj" \
	"$(INTDIR)\drawtile.obj" \
	"$(INTDIR)\gradient.obj" \
	"$(INTDIR)\pgrect.obj" \
	"$(INTDIR)\rotozoom.obj" \
	"$(INTDIR)\setpixel.obj" \
	"$(INTDIR)\stretch.obj" \
	"$(INTDIR)\surface.obj" \
	"$(INTDIR)\dir.obj" \
	"$(INTDIR)\physfs.obj" \
	"$(INTDIR)\unzip.obj" \
	"$(INTDIR)\win32.obj" \
	"$(INTDIR)\zip.obj" \
	"$(INTDIR)\pgbutton.obj" \
	"$(INTDIR)\pgbuttongroup.obj" \
	"$(INTDIR)\pgcheckbutton.obj" \
	"$(INTDIR)\pgcolumnitem.obj" \
	"$(INTDIR)\pgdropdown.obj" \
	"$(INTDIR)\pgimage.obj" \
	"$(INTDIR)\pglabel.obj" \
	"$(INTDIR)\pglayout.obj" \
	"$(INTDIR)\pglineedit.obj" \
	"$(INTDIR)\pglistbox.obj" \
	"$(INTDIR)\pglistboxbaseitem.obj" \
	"$(INTDIR)\pglistboxitem.obj" \
	"$(INTDIR)\pgmaskedit.obj" \
	"$(INTDIR)\pgmenubar.obj" \
	"$(INTDIR)\pgmessagebox.obj" \
	"$(INTDIR)\pgpopupmenu.obj" \
	"$(INTDIR)\pgprogressbar.obj" \
	"$(INTDIR)\pgradiobutton.obj" \
	"$(INTDIR)\pgrichedit.obj" \
	"$(INTDIR)\pgscrollbar.obj" \
	"$(INTDIR)\pgslider.obj" \
	"$(INTDIR)\pgspinnerbox.obj" \
	"$(INTDIR)\pgthemewidget.obj" \
	"$(INTDIR)\pgwidget.obj" \
	"$(INTDIR)\pgwidgetdnd.obj" \
	"$(INTDIR)\pgwidgetlist.obj" \
	"$(INTDIR)\pgwidgetlistex.obj" \
	"$(INTDIR)\pgwindow.obj" \
	"$(INTDIR)\paragui.obj"

"..\..\lib\paraguis.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "paragui_static - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\..\lib\paraguisd.lib"


CLEAN :
	-@erase "$(INTDIR)\dir.obj"
	-@erase "$(INTDIR)\drawline.obj"
	-@erase "$(INTDIR)\drawtile.obj"
	-@erase "$(INTDIR)\gradient.obj"
	-@erase "$(INTDIR)\missing.obj"
	-@erase "$(INTDIR)\paragui.obj"
	-@erase "$(INTDIR)\pgapplication.obj"
	-@erase "$(INTDIR)\pgbutton.obj"
	-@erase "$(INTDIR)\pgbuttongroup.obj"
	-@erase "$(INTDIR)\pgcheckbutton.obj"
	-@erase "$(INTDIR)\pgcolors.obj"
	-@erase "$(INTDIR)\pgcolumnitem.obj"
	-@erase "$(INTDIR)\pgdatacontainer.obj"
	-@erase "$(INTDIR)\pgdropdown.obj"
	-@erase "$(INTDIR)\pgeventobject.obj"
	-@erase "$(INTDIR)\pgfile.obj"
	-@erase "$(INTDIR)\pgfilearchive.obj"
	-@erase "$(INTDIR)\pgfont.obj"
	-@erase "$(INTDIR)\pgfont_impl.obj"
	-@erase "$(INTDIR)\pgimage.obj"
	-@erase "$(INTDIR)\pglabel.obj"
	-@erase "$(INTDIR)\pglayout.obj"
	-@erase "$(INTDIR)\pglineedit.obj"
	-@erase "$(INTDIR)\pglistbox.obj"
	-@erase "$(INTDIR)\pglistboxbaseitem.obj"
	-@erase "$(INTDIR)\pglistboxitem.obj"
	-@erase "$(INTDIR)\pglog.obj"
	-@erase "$(INTDIR)\pgmain.obj"
	-@erase "$(INTDIR)\pgmaskedit.obj"
	-@erase "$(INTDIR)\pgmenubar.obj"
	-@erase "$(INTDIR)\pgmessagebox.obj"
	-@erase "$(INTDIR)\pgmessageobject.obj"
	-@erase "$(INTDIR)\pgmsgmap.obj"
	-@erase "$(INTDIR)\pgnavigator.obj"
	-@erase "$(INTDIR)\pgpopupmenu.obj"
	-@erase "$(INTDIR)\pgprogressbar.obj"
	-@erase "$(INTDIR)\pgradiobutton.obj"
	-@erase "$(INTDIR)\pgrect.obj"
	-@erase "$(INTDIR)\pgrectlist.obj"
	-@erase "$(INTDIR)\pgrichedit.obj"
	-@erase "$(INTDIR)\pgscrollbar.obj"
	-@erase "$(INTDIR)\pgslider.obj"
	-@erase "$(INTDIR)\pgspinnerbox.obj"
	-@erase "$(INTDIR)\pgsurfacecache.obj"
	-@erase "$(INTDIR)\pgthemewidget.obj"
	-@erase "$(INTDIR)\pgwidget.obj"
	-@erase "$(INTDIR)\pgwidgetdnd.obj"
	-@erase "$(INTDIR)\pgwidgetlist.obj"
	-@erase "$(INTDIR)\pgwidgetlistex.obj"
	-@erase "$(INTDIR)\pgwindow.obj"
	-@erase "$(INTDIR)\physfs.obj"
	-@erase "$(INTDIR)\rotozoom.obj"
	-@erase "$(INTDIR)\setpixel.obj"
	-@erase "$(INTDIR)\stretch.obj"
	-@erase "$(INTDIR)\surface.obj"
	-@erase "$(INTDIR)\unzip.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\win32.obj"
	-@erase "$(INTDIR)\zip.obj"
	-@erase "..\..\lib\paraguisd.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /vmg /GX /ZI /Od /I "../../src/physfs" /I "../../src/themes" /I "../../src" /I "../../include" /D "HAVE_SDLIMAGE" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "PHYSFS_SUPPORTS_ZIP" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\paragui_static.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"../../lib/paraguisd.lib" 
LIB32_OBJS= \
	"$(INTDIR)\missing.obj" \
	"$(INTDIR)\pgapplication.obj" \
	"$(INTDIR)\pgcolors.obj" \
	"$(INTDIR)\pgdatacontainer.obj" \
	"$(INTDIR)\pgeventobject.obj" \
	"$(INTDIR)\pgfile.obj" \
	"$(INTDIR)\pgfilearchive.obj" \
	"$(INTDIR)\pglog.obj" \
	"$(INTDIR)\pgmain.obj" \
	"$(INTDIR)\pgmessageobject.obj" \
	"$(INTDIR)\pgmsgmap.obj" \
	"$(INTDIR)\pgnavigator.obj" \
	"$(INTDIR)\pgrectlist.obj" \
	"$(INTDIR)\pgsurfacecache.obj" \
	"$(INTDIR)\pgfont.obj" \
	"$(INTDIR)\pgfont_impl.obj" \
	"$(INTDIR)\drawline.obj" \
	"$(INTDIR)\drawtile.obj" \
	"$(INTDIR)\gradient.obj" \
	"$(INTDIR)\pgrect.obj" \
	"$(INTDIR)\rotozoom.obj" \
	"$(INTDIR)\setpixel.obj" \
	"$(INTDIR)\stretch.obj" \
	"$(INTDIR)\surface.obj" \
	"$(INTDIR)\dir.obj" \
	"$(INTDIR)\physfs.obj" \
	"$(INTDIR)\unzip.obj" \
	"$(INTDIR)\win32.obj" \
	"$(INTDIR)\zip.obj" \
	"$(INTDIR)\pgbutton.obj" \
	"$(INTDIR)\pgbuttongroup.obj" \
	"$(INTDIR)\pgcheckbutton.obj" \
	"$(INTDIR)\pgcolumnitem.obj" \
	"$(INTDIR)\pgdropdown.obj" \
	"$(INTDIR)\pgimage.obj" \
	"$(INTDIR)\pglabel.obj" \
	"$(INTDIR)\pglayout.obj" \
	"$(INTDIR)\pglineedit.obj" \
	"$(INTDIR)\pglistbox.obj" \
	"$(INTDIR)\pglistboxbaseitem.obj" \
	"$(INTDIR)\pglistboxitem.obj" \
	"$(INTDIR)\pgmaskedit.obj" \
	"$(INTDIR)\pgmenubar.obj" \
	"$(INTDIR)\pgmessagebox.obj" \
	"$(INTDIR)\pgpopupmenu.obj" \
	"$(INTDIR)\pgprogressbar.obj" \
	"$(INTDIR)\pgradiobutton.obj" \
	"$(INTDIR)\pgrichedit.obj" \
	"$(INTDIR)\pgscrollbar.obj" \
	"$(INTDIR)\pgslider.obj" \
	"$(INTDIR)\pgspinnerbox.obj" \
	"$(INTDIR)\pgthemewidget.obj" \
	"$(INTDIR)\pgwidget.obj" \
	"$(INTDIR)\pgwidgetdnd.obj" \
	"$(INTDIR)\pgwidgetlist.obj" \
	"$(INTDIR)\pgwidgetlistex.obj" \
	"$(INTDIR)\pgwindow.obj" \
	"$(INTDIR)\paragui.obj"

"..\..\lib\paraguisd.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "paragui_static - Win32 Release MT"

OUTDIR=.\ReleaseMT
INTDIR=.\ReleaseMT

ALL : "..\..\lib\paraguimts.lib"


CLEAN :
	-@erase "$(INTDIR)\dir.obj"
	-@erase "$(INTDIR)\drawline.obj"
	-@erase "$(INTDIR)\drawtile.obj"
	-@erase "$(INTDIR)\gradient.obj"
	-@erase "$(INTDIR)\missing.obj"
	-@erase "$(INTDIR)\paragui.obj"
	-@erase "$(INTDIR)\pgapplication.obj"
	-@erase "$(INTDIR)\pgbutton.obj"
	-@erase "$(INTDIR)\pgbuttongroup.obj"
	-@erase "$(INTDIR)\pgcheckbutton.obj"
	-@erase "$(INTDIR)\pgcolors.obj"
	-@erase "$(INTDIR)\pgcolumnitem.obj"
	-@erase "$(INTDIR)\pgdatacontainer.obj"
	-@erase "$(INTDIR)\pgdropdown.obj"
	-@erase "$(INTDIR)\pgeventobject.obj"
	-@erase "$(INTDIR)\pgfile.obj"
	-@erase "$(INTDIR)\pgfilearchive.obj"
	-@erase "$(INTDIR)\pgfont.obj"
	-@erase "$(INTDIR)\pgfont_impl.obj"
	-@erase "$(INTDIR)\pgimage.obj"
	-@erase "$(INTDIR)\pglabel.obj"
	-@erase "$(INTDIR)\pglayout.obj"
	-@erase "$(INTDIR)\pglineedit.obj"
	-@erase "$(INTDIR)\pglistbox.obj"
	-@erase "$(INTDIR)\pglistboxbaseitem.obj"
	-@erase "$(INTDIR)\pglistboxitem.obj"
	-@erase "$(INTDIR)\pglog.obj"
	-@erase "$(INTDIR)\pgmain.obj"
	-@erase "$(INTDIR)\pgmaskedit.obj"
	-@erase "$(INTDIR)\pgmenubar.obj"
	-@erase "$(INTDIR)\pgmessagebox.obj"
	-@erase "$(INTDIR)\pgmessageobject.obj"
	-@erase "$(INTDIR)\pgmsgmap.obj"
	-@erase "$(INTDIR)\pgnavigator.obj"
	-@erase "$(INTDIR)\pgpopupmenu.obj"
	-@erase "$(INTDIR)\pgprogressbar.obj"
	-@erase "$(INTDIR)\pgradiobutton.obj"
	-@erase "$(INTDIR)\pgrect.obj"
	-@erase "$(INTDIR)\pgrectlist.obj"
	-@erase "$(INTDIR)\pgrichedit.obj"
	-@erase "$(INTDIR)\pgscrollbar.obj"
	-@erase "$(INTDIR)\pgslider.obj"
	-@erase "$(INTDIR)\pgspinnerbox.obj"
	-@erase "$(INTDIR)\pgsurfacecache.obj"
	-@erase "$(INTDIR)\pgthemewidget.obj"
	-@erase "$(INTDIR)\pgwidget.obj"
	-@erase "$(INTDIR)\pgwidgetdnd.obj"
	-@erase "$(INTDIR)\pgwidgetlist.obj"
	-@erase "$(INTDIR)\pgwidgetlistex.obj"
	-@erase "$(INTDIR)\pgwindow.obj"
	-@erase "$(INTDIR)\physfs.obj"
	-@erase "$(INTDIR)\rotozoom.obj"
	-@erase "$(INTDIR)\setpixel.obj"
	-@erase "$(INTDIR)\stretch.obj"
	-@erase "$(INTDIR)\surface.obj"
	-@erase "$(INTDIR)\unzip.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\win32.obj"
	-@erase "$(INTDIR)\zip.obj"
	-@erase "..\..\lib\paraguimts.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /vmg /GX /O2 /I "../../src/physfs" /I "../../src/themes" /I "../../src" /I "../../include" /D "HAVE_SDLIMAGE" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "PHYSFS_SUPPORTS_ZIP" /Fp"$(INTDIR)\paragui_static.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\paragui_static.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"../../lib/paraguimts.lib" 
LIB32_OBJS= \
	"$(INTDIR)\missing.obj" \
	"$(INTDIR)\pgapplication.obj" \
	"$(INTDIR)\pgcolors.obj" \
	"$(INTDIR)\pgdatacontainer.obj" \
	"$(INTDIR)\pgeventobject.obj" \
	"$(INTDIR)\pgfile.obj" \
	"$(INTDIR)\pgfilearchive.obj" \
	"$(INTDIR)\pglog.obj" \
	"$(INTDIR)\pgmain.obj" \
	"$(INTDIR)\pgmessageobject.obj" \
	"$(INTDIR)\pgmsgmap.obj" \
	"$(INTDIR)\pgnavigator.obj" \
	"$(INTDIR)\pgrectlist.obj" \
	"$(INTDIR)\pgsurfacecache.obj" \
	"$(INTDIR)\pgfont.obj" \
	"$(INTDIR)\pgfont_impl.obj" \
	"$(INTDIR)\drawline.obj" \
	"$(INTDIR)\drawtile.obj" \
	"$(INTDIR)\gradient.obj" \
	"$(INTDIR)\pgrect.obj" \
	"$(INTDIR)\rotozoom.obj" \
	"$(INTDIR)\setpixel.obj" \
	"$(INTDIR)\stretch.obj" \
	"$(INTDIR)\surface.obj" \
	"$(INTDIR)\dir.obj" \
	"$(INTDIR)\physfs.obj" \
	"$(INTDIR)\unzip.obj" \
	"$(INTDIR)\win32.obj" \
	"$(INTDIR)\zip.obj" \
	"$(INTDIR)\pgbutton.obj" \
	"$(INTDIR)\pgbuttongroup.obj" \
	"$(INTDIR)\pgcheckbutton.obj" \
	"$(INTDIR)\pgcolumnitem.obj" \
	"$(INTDIR)\pgdropdown.obj" \
	"$(INTDIR)\pgimage.obj" \
	"$(INTDIR)\pglabel.obj" \
	"$(INTDIR)\pglayout.obj" \
	"$(INTDIR)\pglineedit.obj" \
	"$(INTDIR)\pglistbox.obj" \
	"$(INTDIR)\pglistboxbaseitem.obj" \
	"$(INTDIR)\pglistboxitem.obj" \
	"$(INTDIR)\pgmaskedit.obj" \
	"$(INTDIR)\pgmenubar.obj" \
	"$(INTDIR)\pgmessagebox.obj" \
	"$(INTDIR)\pgpopupmenu.obj" \
	"$(INTDIR)\pgprogressbar.obj" \
	"$(INTDIR)\pgradiobutton.obj" \
	"$(INTDIR)\pgrichedit.obj" \
	"$(INTDIR)\pgscrollbar.obj" \
	"$(INTDIR)\pgslider.obj" \
	"$(INTDIR)\pgspinnerbox.obj" \
	"$(INTDIR)\pgthemewidget.obj" \
	"$(INTDIR)\pgwidget.obj" \
	"$(INTDIR)\pgwidgetdnd.obj" \
	"$(INTDIR)\pgwidgetlist.obj" \
	"$(INTDIR)\pgwidgetlistex.obj" \
	"$(INTDIR)\pgwindow.obj" \
	"$(INTDIR)\paragui.obj"

"..\..\lib\paraguimts.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "paragui_static - Win32 Debug MT"

OUTDIR=.\DebugMT
INTDIR=.\DebugMT

ALL : "..\..\lib\paraguimtsd.lib"


CLEAN :
	-@erase "$(INTDIR)\dir.obj"
	-@erase "$(INTDIR)\drawline.obj"
	-@erase "$(INTDIR)\drawtile.obj"
	-@erase "$(INTDIR)\gradient.obj"
	-@erase "$(INTDIR)\missing.obj"
	-@erase "$(INTDIR)\paragui.obj"
	-@erase "$(INTDIR)\pgapplication.obj"
	-@erase "$(INTDIR)\pgbutton.obj"
	-@erase "$(INTDIR)\pgbuttongroup.obj"
	-@erase "$(INTDIR)\pgcheckbutton.obj"
	-@erase "$(INTDIR)\pgcolors.obj"
	-@erase "$(INTDIR)\pgcolumnitem.obj"
	-@erase "$(INTDIR)\pgdatacontainer.obj"
	-@erase "$(INTDIR)\pgdropdown.obj"
	-@erase "$(INTDIR)\pgeventobject.obj"
	-@erase "$(INTDIR)\pgfile.obj"
	-@erase "$(INTDIR)\pgfilearchive.obj"
	-@erase "$(INTDIR)\pgfont.obj"
	-@erase "$(INTDIR)\pgfont_impl.obj"
	-@erase "$(INTDIR)\pgimage.obj"
	-@erase "$(INTDIR)\pglabel.obj"
	-@erase "$(INTDIR)\pglayout.obj"
	-@erase "$(INTDIR)\pglineedit.obj"
	-@erase "$(INTDIR)\pglistbox.obj"
	-@erase "$(INTDIR)\pglistboxbaseitem.obj"
	-@erase "$(INTDIR)\pglistboxitem.obj"
	-@erase "$(INTDIR)\pglog.obj"
	-@erase "$(INTDIR)\pgmain.obj"
	-@erase "$(INTDIR)\pgmaskedit.obj"
	-@erase "$(INTDIR)\pgmenubar.obj"
	-@erase "$(INTDIR)\pgmessagebox.obj"
	-@erase "$(INTDIR)\pgmessageobject.obj"
	-@erase "$(INTDIR)\pgmsgmap.obj"
	-@erase "$(INTDIR)\pgnavigator.obj"
	-@erase "$(INTDIR)\pgpopupmenu.obj"
	-@erase "$(INTDIR)\pgprogressbar.obj"
	-@erase "$(INTDIR)\pgradiobutton.obj"
	-@erase "$(INTDIR)\pgrect.obj"
	-@erase "$(INTDIR)\pgrectlist.obj"
	-@erase "$(INTDIR)\pgrichedit.obj"
	-@erase "$(INTDIR)\pgscrollbar.obj"
	-@erase "$(INTDIR)\pgslider.obj"
	-@erase "$(INTDIR)\pgspinnerbox.obj"
	-@erase "$(INTDIR)\pgsurfacecache.obj"
	-@erase "$(INTDIR)\pgthemewidget.obj"
	-@erase "$(INTDIR)\pgwidget.obj"
	-@erase "$(INTDIR)\pgwidgetdnd.obj"
	-@erase "$(INTDIR)\pgwidgetlist.obj"
	-@erase "$(INTDIR)\pgwidgetlistex.obj"
	-@erase "$(INTDIR)\pgwindow.obj"
	-@erase "$(INTDIR)\physfs.obj"
	-@erase "$(INTDIR)\rotozoom.obj"
	-@erase "$(INTDIR)\setpixel.obj"
	-@erase "$(INTDIR)\stretch.obj"
	-@erase "$(INTDIR)\surface.obj"
	-@erase "$(INTDIR)\unzip.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\win32.obj"
	-@erase "$(INTDIR)\zip.obj"
	-@erase "..\..\lib\paraguimtsd.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /vmg /GX /ZI /Od /I "../../src/physfs" /I "../../src/themes" /I "../../src" /I "../../include" /D "HAVE_SDLIMAGE" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "PHYSFS_SUPPORTS_ZIP" /Fp"$(INTDIR)\paragui_static.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\paragui_static.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"../../lib/paraguimtsd.lib" 
LIB32_OBJS= \
	"$(INTDIR)\missing.obj" \
	"$(INTDIR)\pgapplication.obj" \
	"$(INTDIR)\pgcolors.obj" \
	"$(INTDIR)\pgdatacontainer.obj" \
	"$(INTDIR)\pgeventobject.obj" \
	"$(INTDIR)\pgfile.obj" \
	"$(INTDIR)\pgfilearchive.obj" \
	"$(INTDIR)\pglog.obj" \
	"$(INTDIR)\pgmain.obj" \
	"$(INTDIR)\pgmessageobject.obj" \
	"$(INTDIR)\pgmsgmap.obj" \
	"$(INTDIR)\pgnavigator.obj" \
	"$(INTDIR)\pgrectlist.obj" \
	"$(INTDIR)\pgsurfacecache.obj" \
	"$(INTDIR)\pgfont.obj" \
	"$(INTDIR)\pgfont_impl.obj" \
	"$(INTDIR)\drawline.obj" \
	"$(INTDIR)\drawtile.obj" \
	"$(INTDIR)\gradient.obj" \
	"$(INTDIR)\pgrect.obj" \
	"$(INTDIR)\rotozoom.obj" \
	"$(INTDIR)\setpixel.obj" \
	"$(INTDIR)\stretch.obj" \
	"$(INTDIR)\surface.obj" \
	"$(INTDIR)\dir.obj" \
	"$(INTDIR)\physfs.obj" \
	"$(INTDIR)\unzip.obj" \
	"$(INTDIR)\win32.obj" \
	"$(INTDIR)\zip.obj" \
	"$(INTDIR)\pgbutton.obj" \
	"$(INTDIR)\pgbuttongroup.obj" \
	"$(INTDIR)\pgcheckbutton.obj" \
	"$(INTDIR)\pgcolumnitem.obj" \
	"$(INTDIR)\pgdropdown.obj" \
	"$(INTDIR)\pgimage.obj" \
	"$(INTDIR)\pglabel.obj" \
	"$(INTDIR)\pglayout.obj" \
	"$(INTDIR)\pglineedit.obj" \
	"$(INTDIR)\pglistbox.obj" \
	"$(INTDIR)\pglistboxbaseitem.obj" \
	"$(INTDIR)\pglistboxitem.obj" \
	"$(INTDIR)\pgmaskedit.obj" \
	"$(INTDIR)\pgmenubar.obj" \
	"$(INTDIR)\pgmessagebox.obj" \
	"$(INTDIR)\pgpopupmenu.obj" \
	"$(INTDIR)\pgprogressbar.obj" \
	"$(INTDIR)\pgradiobutton.obj" \
	"$(INTDIR)\pgrichedit.obj" \
	"$(INTDIR)\pgscrollbar.obj" \
	"$(INTDIR)\pgslider.obj" \
	"$(INTDIR)\pgspinnerbox.obj" \
	"$(INTDIR)\pgthemewidget.obj" \
	"$(INTDIR)\pgwidget.obj" \
	"$(INTDIR)\pgwidgetdnd.obj" \
	"$(INTDIR)\pgwidgetlist.obj" \
	"$(INTDIR)\pgwidgetlistex.obj" \
	"$(INTDIR)\pgwindow.obj" \
	"$(INTDIR)\paragui.obj"

"..\..\lib\paraguimtsd.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("paragui_static.dep")
!INCLUDE "paragui_static.dep"
!ELSE 
!MESSAGE Warning: cannot find "paragui_static.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "paragui_static - Win32 Release" || "$(CFG)" == "paragui_static - Win32 Debug" || "$(CFG)" == "paragui_static - Win32 Release MT" || "$(CFG)" == "paragui_static - Win32 Debug MT"
SOURCE=..\..\src\core\missing.cpp

"$(INTDIR)\missing.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\core\pgapplication.cpp

"$(INTDIR)\pgapplication.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\core\pgcolors.cpp

"$(INTDIR)\pgcolors.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\core\pgdatacontainer.cpp

"$(INTDIR)\pgdatacontainer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\core\pgeventobject.cpp

"$(INTDIR)\pgeventobject.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\core\pgfile.cpp

"$(INTDIR)\pgfile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\core\pgfilearchive.cpp

"$(INTDIR)\pgfilearchive.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\core\pglog.cpp

"$(INTDIR)\pglog.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\core\pgmain.cpp

"$(INTDIR)\pgmain.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\core\pgmessageobject.cpp

"$(INTDIR)\pgmessageobject.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\core\pgmsgmap.cpp

"$(INTDIR)\pgmsgmap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\core\pgnavigator.cpp

"$(INTDIR)\pgnavigator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\core\pgrectlist.cpp

"$(INTDIR)\pgrectlist.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\core\pgsurfacecache.cpp

"$(INTDIR)\pgsurfacecache.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\font\pgfont.cpp

"$(INTDIR)\pgfont.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\font\pgfont_impl.cpp

"$(INTDIR)\pgfont_impl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\draw\drawline.cpp

"$(INTDIR)\drawline.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\draw\drawtile.cpp

"$(INTDIR)\drawtile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\draw\gradient.cpp

"$(INTDIR)\gradient.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\draw\pgrect.cpp

"$(INTDIR)\pgrect.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\draw\rotozoom.cpp

"$(INTDIR)\rotozoom.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\draw\setpixel.cpp

"$(INTDIR)\setpixel.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\draw\stretch.cpp

"$(INTDIR)\stretch.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\draw\surface.cpp

"$(INTDIR)\surface.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\physfs\archivers\dir.c

"$(INTDIR)\dir.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\physfs\physfs.c

"$(INTDIR)\physfs.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\physfs\archivers\unzip.c

"$(INTDIR)\unzip.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\physfs\platform\win32.c

"$(INTDIR)\win32.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\physfs\archivers\zip.c

"$(INTDIR)\zip.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\widgets\pgbutton.cpp

"$(INTDIR)\pgbutton.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\widgets\pgbuttongroup.cpp

"$(INTDIR)\pgbuttongroup.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\widgets\pgcheckbutton.cpp

"$(INTDIR)\pgcheckbutton.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\widgets\pgcolumnitem.cpp

"$(INTDIR)\pgcolumnitem.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\widgets\pgdropdown.cpp

"$(INTDIR)\pgdropdown.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\widgets\pgimage.cpp

"$(INTDIR)\pgimage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\widgets\pglabel.cpp

"$(INTDIR)\pglabel.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\widgets\pglayout.cpp

"$(INTDIR)\pglayout.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\widgets\pglineedit.cpp

"$(INTDIR)\pglineedit.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\widgets\pglistbox.cpp

"$(INTDIR)\pglistbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\widgets\pglistboxbaseitem.cpp

"$(INTDIR)\pglistboxbaseitem.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\widgets\pglistboxitem.cpp

"$(INTDIR)\pglistboxitem.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\widgets\pgmaskedit.cpp

"$(INTDIR)\pgmaskedit.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\widgets\pgmenubar.cpp

"$(INTDIR)\pgmenubar.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\widgets\pgmessagebox.cpp

"$(INTDIR)\pgmessagebox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\widgets\pgpopupmenu.cpp

"$(INTDIR)\pgpopupmenu.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\widgets\pgprogressbar.cpp

"$(INTDIR)\pgprogressbar.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\widgets\pgradiobutton.cpp

"$(INTDIR)\pgradiobutton.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\widgets\pgrichedit.cpp

"$(INTDIR)\pgrichedit.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\widgets\pgscrollbar.cpp

"$(INTDIR)\pgscrollbar.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\widgets\pgslider.cpp

"$(INTDIR)\pgslider.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\widgets\pgspinnerbox.cpp

"$(INTDIR)\pgspinnerbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\widgets\pgthemewidget.cpp

"$(INTDIR)\pgthemewidget.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\widgets\pgwidget.cpp

"$(INTDIR)\pgwidget.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\widgets\pgwidgetdnd.cpp

"$(INTDIR)\pgwidgetdnd.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\widgets\pgwidgetlist.cpp

"$(INTDIR)\pgwidgetlist.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\widgets\pgwidgetlistex.cpp

"$(INTDIR)\pgwidgetlistex.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\widgets\pgwindow.cpp

"$(INTDIR)\pgwindow.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\paragui.cpp

"$(INTDIR)\paragui.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

