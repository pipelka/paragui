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
	-@erase "$(INTDIR)\grp.obj"
	-@erase "$(INTDIR)\parastretch.obj"
	-@erase "$(INTDIR)\pgapplication.obj"
	-@erase "$(INTDIR)\pgbutton.obj"
	-@erase "$(INTDIR)\pgbuttongroup.obj"
	-@erase "$(INTDIR)\pgcheckbutton.obj"
	-@erase "$(INTDIR)\pgcolumnitem.obj"
	-@erase "$(INTDIR)\pgdrawline.obj"
	-@erase "$(INTDIR)\pgdrawobject.obj"
	-@erase "$(INTDIR)\pgdropdown.obj"
	-@erase "$(INTDIR)\pgeventobject.obj"
	-@erase "$(INTDIR)\pgfile.obj"
	-@erase "$(INTDIR)\pgfilearchive.obj"
	-@erase "$(INTDIR)\pgfont.obj"
	-@erase "$(INTDIR)\pggradientwidget.obj"
	-@erase "$(INTDIR)\pgimage.obj"
	-@erase "$(INTDIR)\pglabel.obj"
	-@erase "$(INTDIR)\pglayout.obj"
	-@erase "$(INTDIR)\pglineedit.obj"
	-@erase "$(INTDIR)\pglistbox.obj"
	-@erase "$(INTDIR)\pglistboxbaseitem.obj"
	-@erase "$(INTDIR)\pglistboxitem.obj"
	-@erase "$(INTDIR)\pglog.obj"
	-@erase "$(INTDIR)\pgmaskedit.obj"
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
	-@erase "$(INTDIR)\pgrotozoom.obj"
	-@erase "$(INTDIR)\pgscrollbar.obj"
	-@erase "$(INTDIR)\pgslider.obj"
	-@erase "$(INTDIR)\pgspinnerbox.obj"
	-@erase "$(INTDIR)\pgstaticframe.obj"
	-@erase "$(INTDIR)\pgsurfacecache.obj"
	-@erase "$(INTDIR)\pgwidget.obj"
	-@erase "$(INTDIR)\pgwidgetdnd.obj"
	-@erase "$(INTDIR)\pgwidgetlist.obj"
	-@erase "$(INTDIR)\pgwidgetlistex.obj"
	-@erase "$(INTDIR)\pgwindow.obj"
	-@erase "$(INTDIR)\physfs.obj"
	-@erase "$(INTDIR)\rendertextrect.obj"
	-@erase "$(INTDIR)\theme_priv.obj"
	-@erase "$(INTDIR)\themeloader.obj"
	-@erase "$(INTDIR)\unzip.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\win32.obj"
	-@erase "$(INTDIR)\zip.obj"
	-@erase "..\..\lib\paraguis.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /vmg /GX /O2 /I "../../physfs" /I "../../themes" /I "../../src" /I "../../include" /D "HAVE_SDLIMAGE" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "PHYSFS_SUPPORTS_ZIP" /Fp"$(INTDIR)\paragui_static.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
	"$(INTDIR)\parastretch.obj" \
	"$(INTDIR)\pgapplication.obj" \
	"$(INTDIR)\pgbutton.obj" \
	"$(INTDIR)\pgbuttongroup.obj" \
	"$(INTDIR)\pgcheckbutton.obj" \
	"$(INTDIR)\pgcolumnitem.obj" \
	"$(INTDIR)\pgdrawline.obj" \
	"$(INTDIR)\pgdrawobject.obj" \
	"$(INTDIR)\pgdropdown.obj" \
	"$(INTDIR)\pgeventobject.obj" \
	"$(INTDIR)\pgfile.obj" \
	"$(INTDIR)\pgfilearchive.obj" \
	"$(INTDIR)\pgfont.obj" \
	"$(INTDIR)\pggradientwidget.obj" \
	"$(INTDIR)\pgimage.obj" \
	"$(INTDIR)\pglabel.obj" \
	"$(INTDIR)\pglayout.obj" \
	"$(INTDIR)\pglineedit.obj" \
	"$(INTDIR)\pglistbox.obj" \
	"$(INTDIR)\pglistboxbaseitem.obj" \
	"$(INTDIR)\pglistboxitem.obj" \
	"$(INTDIR)\pglog.obj" \
	"$(INTDIR)\pgmaskedit.obj" \
	"$(INTDIR)\pgmessagebox.obj" \
	"$(INTDIR)\pgmessageobject.obj" \
	"$(INTDIR)\pgmsgmap.obj" \
	"$(INTDIR)\pgnavigator.obj" \
	"$(INTDIR)\pgpopupmenu.obj" \
	"$(INTDIR)\pgprogressbar.obj" \
	"$(INTDIR)\pgradiobutton.obj" \
	"$(INTDIR)\pgrect.obj" \
	"$(INTDIR)\pgrectlist.obj" \
	"$(INTDIR)\pgrichedit.obj" \
	"$(INTDIR)\pgrotozoom.obj" \
	"$(INTDIR)\pgscrollbar.obj" \
	"$(INTDIR)\pgslider.obj" \
	"$(INTDIR)\pgspinnerbox.obj" \
	"$(INTDIR)\pgstaticframe.obj" \
	"$(INTDIR)\pgsurfacecache.obj" \
	"$(INTDIR)\pgwidget.obj" \
	"$(INTDIR)\pgwidgetdnd.obj" \
	"$(INTDIR)\pgwidgetlist.obj" \
	"$(INTDIR)\pgwidgetlistex.obj" \
	"$(INTDIR)\pgwindow.obj" \
	"$(INTDIR)\rendertextrect.obj" \
	"$(INTDIR)\theme_priv.obj" \
	"$(INTDIR)\themeloader.obj" \
	"$(INTDIR)\dir.obj" \
	"$(INTDIR)\grp.obj" \
	"$(INTDIR)\physfs.obj" \
	"$(INTDIR)\unzip.obj" \
	"$(INTDIR)\win32.obj" \
	"$(INTDIR)\zip.obj"

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
	-@erase "$(INTDIR)\grp.obj"
	-@erase "$(INTDIR)\parastretch.obj"
	-@erase "$(INTDIR)\pgapplication.obj"
	-@erase "$(INTDIR)\pgbutton.obj"
	-@erase "$(INTDIR)\pgbuttongroup.obj"
	-@erase "$(INTDIR)\pgcheckbutton.obj"
	-@erase "$(INTDIR)\pgcolumnitem.obj"
	-@erase "$(INTDIR)\pgdrawline.obj"
	-@erase "$(INTDIR)\pgdrawobject.obj"
	-@erase "$(INTDIR)\pgdropdown.obj"
	-@erase "$(INTDIR)\pgeventobject.obj"
	-@erase "$(INTDIR)\pgfile.obj"
	-@erase "$(INTDIR)\pgfilearchive.obj"
	-@erase "$(INTDIR)\pgfont.obj"
	-@erase "$(INTDIR)\pggradientwidget.obj"
	-@erase "$(INTDIR)\pgimage.obj"
	-@erase "$(INTDIR)\pglabel.obj"
	-@erase "$(INTDIR)\pglayout.obj"
	-@erase "$(INTDIR)\pglineedit.obj"
	-@erase "$(INTDIR)\pglistbox.obj"
	-@erase "$(INTDIR)\pglistboxbaseitem.obj"
	-@erase "$(INTDIR)\pglistboxitem.obj"
	-@erase "$(INTDIR)\pglog.obj"
	-@erase "$(INTDIR)\pgmaskedit.obj"
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
	-@erase "$(INTDIR)\pgrotozoom.obj"
	-@erase "$(INTDIR)\pgscrollbar.obj"
	-@erase "$(INTDIR)\pgslider.obj"
	-@erase "$(INTDIR)\pgspinnerbox.obj"
	-@erase "$(INTDIR)\pgstaticframe.obj"
	-@erase "$(INTDIR)\pgsurfacecache.obj"
	-@erase "$(INTDIR)\pgwidget.obj"
	-@erase "$(INTDIR)\pgwidgetdnd.obj"
	-@erase "$(INTDIR)\pgwidgetlist.obj"
	-@erase "$(INTDIR)\pgwidgetlistex.obj"
	-@erase "$(INTDIR)\pgwindow.obj"
	-@erase "$(INTDIR)\physfs.obj"
	-@erase "$(INTDIR)\rendertextrect.obj"
	-@erase "$(INTDIR)\theme_priv.obj"
	-@erase "$(INTDIR)\themeloader.obj"
	-@erase "$(INTDIR)\unzip.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\win32.obj"
	-@erase "$(INTDIR)\zip.obj"
	-@erase "..\..\lib\paraguisd.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /vmg /GX /ZI /Od /I "../../physfs" /I "../../themes" /I "../../src" /I "../../include" /D "HAVE_SDLIMAGE" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "PHYSFS_SUPPORTS_ZIP" /Fp"$(INTDIR)\paragui_static.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
	"$(INTDIR)\parastretch.obj" \
	"$(INTDIR)\pgapplication.obj" \
	"$(INTDIR)\pgbutton.obj" \
	"$(INTDIR)\pgbuttongroup.obj" \
	"$(INTDIR)\pgcheckbutton.obj" \
	"$(INTDIR)\pgcolumnitem.obj" \
	"$(INTDIR)\pgdrawline.obj" \
	"$(INTDIR)\pgdrawobject.obj" \
	"$(INTDIR)\pgdropdown.obj" \
	"$(INTDIR)\pgeventobject.obj" \
	"$(INTDIR)\pgfile.obj" \
	"$(INTDIR)\pgfilearchive.obj" \
	"$(INTDIR)\pgfont.obj" \
	"$(INTDIR)\pggradientwidget.obj" \
	"$(INTDIR)\pgimage.obj" \
	"$(INTDIR)\pglabel.obj" \
	"$(INTDIR)\pglayout.obj" \
	"$(INTDIR)\pglineedit.obj" \
	"$(INTDIR)\pglistbox.obj" \
	"$(INTDIR)\pglistboxbaseitem.obj" \
	"$(INTDIR)\pglistboxitem.obj" \
	"$(INTDIR)\pglog.obj" \
	"$(INTDIR)\pgmaskedit.obj" \
	"$(INTDIR)\pgmessagebox.obj" \
	"$(INTDIR)\pgmessageobject.obj" \
	"$(INTDIR)\pgmsgmap.obj" \
	"$(INTDIR)\pgnavigator.obj" \
	"$(INTDIR)\pgpopupmenu.obj" \
	"$(INTDIR)\pgprogressbar.obj" \
	"$(INTDIR)\pgradiobutton.obj" \
	"$(INTDIR)\pgrect.obj" \
	"$(INTDIR)\pgrectlist.obj" \
	"$(INTDIR)\pgrichedit.obj" \
	"$(INTDIR)\pgrotozoom.obj" \
	"$(INTDIR)\pgscrollbar.obj" \
	"$(INTDIR)\pgslider.obj" \
	"$(INTDIR)\pgspinnerbox.obj" \
	"$(INTDIR)\pgstaticframe.obj" \
	"$(INTDIR)\pgsurfacecache.obj" \
	"$(INTDIR)\pgwidget.obj" \
	"$(INTDIR)\pgwidgetdnd.obj" \
	"$(INTDIR)\pgwidgetlist.obj" \
	"$(INTDIR)\pgwidgetlistex.obj" \
	"$(INTDIR)\pgwindow.obj" \
	"$(INTDIR)\rendertextrect.obj" \
	"$(INTDIR)\theme_priv.obj" \
	"$(INTDIR)\themeloader.obj" \
	"$(INTDIR)\dir.obj" \
	"$(INTDIR)\grp.obj" \
	"$(INTDIR)\physfs.obj" \
	"$(INTDIR)\unzip.obj" \
	"$(INTDIR)\win32.obj" \
	"$(INTDIR)\zip.obj"

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
	-@erase "$(INTDIR)\grp.obj"
	-@erase "$(INTDIR)\parastretch.obj"
	-@erase "$(INTDIR)\pgapplication.obj"
	-@erase "$(INTDIR)\pgbutton.obj"
	-@erase "$(INTDIR)\pgbuttongroup.obj"
	-@erase "$(INTDIR)\pgcheckbutton.obj"
	-@erase "$(INTDIR)\pgcolumnitem.obj"
	-@erase "$(INTDIR)\pgdrawline.obj"
	-@erase "$(INTDIR)\pgdrawobject.obj"
	-@erase "$(INTDIR)\pgdropdown.obj"
	-@erase "$(INTDIR)\pgeventobject.obj"
	-@erase "$(INTDIR)\pgfile.obj"
	-@erase "$(INTDIR)\pgfilearchive.obj"
	-@erase "$(INTDIR)\pgfont.obj"
	-@erase "$(INTDIR)\pggradientwidget.obj"
	-@erase "$(INTDIR)\pgimage.obj"
	-@erase "$(INTDIR)\pglabel.obj"
	-@erase "$(INTDIR)\pglayout.obj"
	-@erase "$(INTDIR)\pglineedit.obj"
	-@erase "$(INTDIR)\pglistbox.obj"
	-@erase "$(INTDIR)\pglistboxbaseitem.obj"
	-@erase "$(INTDIR)\pglistboxitem.obj"
	-@erase "$(INTDIR)\pglog.obj"
	-@erase "$(INTDIR)\pgmaskedit.obj"
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
	-@erase "$(INTDIR)\pgrotozoom.obj"
	-@erase "$(INTDIR)\pgscrollbar.obj"
	-@erase "$(INTDIR)\pgslider.obj"
	-@erase "$(INTDIR)\pgspinnerbox.obj"
	-@erase "$(INTDIR)\pgstaticframe.obj"
	-@erase "$(INTDIR)\pgsurfacecache.obj"
	-@erase "$(INTDIR)\pgwidget.obj"
	-@erase "$(INTDIR)\pgwidgetdnd.obj"
	-@erase "$(INTDIR)\pgwidgetlist.obj"
	-@erase "$(INTDIR)\pgwidgetlistex.obj"
	-@erase "$(INTDIR)\pgwindow.obj"
	-@erase "$(INTDIR)\physfs.obj"
	-@erase "$(INTDIR)\rendertextrect.obj"
	-@erase "$(INTDIR)\theme_priv.obj"
	-@erase "$(INTDIR)\themeloader.obj"
	-@erase "$(INTDIR)\unzip.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\win32.obj"
	-@erase "$(INTDIR)\zip.obj"
	-@erase "..\..\lib\paraguimts.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /vmg /GX /O2 /I "../../physfs" /I "../../themes" /I "../../src" /I "../../include" /D "HAVE_SDLIMAGE" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "PHYSFS_SUPPORTS_ZIP" /Fp"$(INTDIR)\paragui_static.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
	"$(INTDIR)\parastretch.obj" \
	"$(INTDIR)\pgapplication.obj" \
	"$(INTDIR)\pgbutton.obj" \
	"$(INTDIR)\pgbuttongroup.obj" \
	"$(INTDIR)\pgcheckbutton.obj" \
	"$(INTDIR)\pgcolumnitem.obj" \
	"$(INTDIR)\pgdrawline.obj" \
	"$(INTDIR)\pgdrawobject.obj" \
	"$(INTDIR)\pgdropdown.obj" \
	"$(INTDIR)\pgeventobject.obj" \
	"$(INTDIR)\pgfile.obj" \
	"$(INTDIR)\pgfilearchive.obj" \
	"$(INTDIR)\pgfont.obj" \
	"$(INTDIR)\pggradientwidget.obj" \
	"$(INTDIR)\pgimage.obj" \
	"$(INTDIR)\pglabel.obj" \
	"$(INTDIR)\pglayout.obj" \
	"$(INTDIR)\pglineedit.obj" \
	"$(INTDIR)\pglistbox.obj" \
	"$(INTDIR)\pglistboxbaseitem.obj" \
	"$(INTDIR)\pglistboxitem.obj" \
	"$(INTDIR)\pglog.obj" \
	"$(INTDIR)\pgmaskedit.obj" \
	"$(INTDIR)\pgmessagebox.obj" \
	"$(INTDIR)\pgmessageobject.obj" \
	"$(INTDIR)\pgmsgmap.obj" \
	"$(INTDIR)\pgnavigator.obj" \
	"$(INTDIR)\pgpopupmenu.obj" \
	"$(INTDIR)\pgprogressbar.obj" \
	"$(INTDIR)\pgradiobutton.obj" \
	"$(INTDIR)\pgrect.obj" \
	"$(INTDIR)\pgrectlist.obj" \
	"$(INTDIR)\pgrichedit.obj" \
	"$(INTDIR)\pgrotozoom.obj" \
	"$(INTDIR)\pgscrollbar.obj" \
	"$(INTDIR)\pgslider.obj" \
	"$(INTDIR)\pgspinnerbox.obj" \
	"$(INTDIR)\pgstaticframe.obj" \
	"$(INTDIR)\pgsurfacecache.obj" \
	"$(INTDIR)\pgwidget.obj" \
	"$(INTDIR)\pgwidgetdnd.obj" \
	"$(INTDIR)\pgwidgetlist.obj" \
	"$(INTDIR)\pgwidgetlistex.obj" \
	"$(INTDIR)\pgwindow.obj" \
	"$(INTDIR)\rendertextrect.obj" \
	"$(INTDIR)\theme_priv.obj" \
	"$(INTDIR)\themeloader.obj" \
	"$(INTDIR)\dir.obj" \
	"$(INTDIR)\grp.obj" \
	"$(INTDIR)\physfs.obj" \
	"$(INTDIR)\unzip.obj" \
	"$(INTDIR)\win32.obj" \
	"$(INTDIR)\zip.obj"

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
	-@erase "$(INTDIR)\grp.obj"
	-@erase "$(INTDIR)\parastretch.obj"
	-@erase "$(INTDIR)\pgapplication.obj"
	-@erase "$(INTDIR)\pgbutton.obj"
	-@erase "$(INTDIR)\pgbuttongroup.obj"
	-@erase "$(INTDIR)\pgcheckbutton.obj"
	-@erase "$(INTDIR)\pgcolumnitem.obj"
	-@erase "$(INTDIR)\pgdrawline.obj"
	-@erase "$(INTDIR)\pgdrawobject.obj"
	-@erase "$(INTDIR)\pgdropdown.obj"
	-@erase "$(INTDIR)\pgeventobject.obj"
	-@erase "$(INTDIR)\pgfile.obj"
	-@erase "$(INTDIR)\pgfilearchive.obj"
	-@erase "$(INTDIR)\pgfont.obj"
	-@erase "$(INTDIR)\pggradientwidget.obj"
	-@erase "$(INTDIR)\pgimage.obj"
	-@erase "$(INTDIR)\pglabel.obj"
	-@erase "$(INTDIR)\pglayout.obj"
	-@erase "$(INTDIR)\pglineedit.obj"
	-@erase "$(INTDIR)\pglistbox.obj"
	-@erase "$(INTDIR)\pglistboxbaseitem.obj"
	-@erase "$(INTDIR)\pglistboxitem.obj"
	-@erase "$(INTDIR)\pglog.obj"
	-@erase "$(INTDIR)\pgmaskedit.obj"
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
	-@erase "$(INTDIR)\pgrotozoom.obj"
	-@erase "$(INTDIR)\pgscrollbar.obj"
	-@erase "$(INTDIR)\pgslider.obj"
	-@erase "$(INTDIR)\pgspinnerbox.obj"
	-@erase "$(INTDIR)\pgstaticframe.obj"
	-@erase "$(INTDIR)\pgsurfacecache.obj"
	-@erase "$(INTDIR)\pgwidget.obj"
	-@erase "$(INTDIR)\pgwidgetdnd.obj"
	-@erase "$(INTDIR)\pgwidgetlist.obj"
	-@erase "$(INTDIR)\pgwidgetlistex.obj"
	-@erase "$(INTDIR)\pgwindow.obj"
	-@erase "$(INTDIR)\physfs.obj"
	-@erase "$(INTDIR)\rendertextrect.obj"
	-@erase "$(INTDIR)\theme_priv.obj"
	-@erase "$(INTDIR)\themeloader.obj"
	-@erase "$(INTDIR)\unzip.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\win32.obj"
	-@erase "$(INTDIR)\zip.obj"
	-@erase "..\..\lib\paraguimtsd.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /vmg /GX /ZI /Od /I "../../physfs" /I "../../themes" /I "../../src" /I "../../include" /D "HAVE_SDLIMAGE" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "PHYSFS_SUPPORTS_ZIP" /Fp"$(INTDIR)\paragui_static.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
	"$(INTDIR)\parastretch.obj" \
	"$(INTDIR)\pgapplication.obj" \
	"$(INTDIR)\pgbutton.obj" \
	"$(INTDIR)\pgbuttongroup.obj" \
	"$(INTDIR)\pgcheckbutton.obj" \
	"$(INTDIR)\pgcolumnitem.obj" \
	"$(INTDIR)\pgdrawline.obj" \
	"$(INTDIR)\pgdrawobject.obj" \
	"$(INTDIR)\pgdropdown.obj" \
	"$(INTDIR)\pgeventobject.obj" \
	"$(INTDIR)\pgfile.obj" \
	"$(INTDIR)\pgfilearchive.obj" \
	"$(INTDIR)\pgfont.obj" \
	"$(INTDIR)\pggradientwidget.obj" \
	"$(INTDIR)\pgimage.obj" \
	"$(INTDIR)\pglabel.obj" \
	"$(INTDIR)\pglayout.obj" \
	"$(INTDIR)\pglineedit.obj" \
	"$(INTDIR)\pglistbox.obj" \
	"$(INTDIR)\pglistboxbaseitem.obj" \
	"$(INTDIR)\pglistboxitem.obj" \
	"$(INTDIR)\pglog.obj" \
	"$(INTDIR)\pgmaskedit.obj" \
	"$(INTDIR)\pgmessagebox.obj" \
	"$(INTDIR)\pgmessageobject.obj" \
	"$(INTDIR)\pgmsgmap.obj" \
	"$(INTDIR)\pgnavigator.obj" \
	"$(INTDIR)\pgpopupmenu.obj" \
	"$(INTDIR)\pgprogressbar.obj" \
	"$(INTDIR)\pgradiobutton.obj" \
	"$(INTDIR)\pgrect.obj" \
	"$(INTDIR)\pgrectlist.obj" \
	"$(INTDIR)\pgrichedit.obj" \
	"$(INTDIR)\pgrotozoom.obj" \
	"$(INTDIR)\pgscrollbar.obj" \
	"$(INTDIR)\pgslider.obj" \
	"$(INTDIR)\pgspinnerbox.obj" \
	"$(INTDIR)\pgstaticframe.obj" \
	"$(INTDIR)\pgsurfacecache.obj" \
	"$(INTDIR)\pgwidget.obj" \
	"$(INTDIR)\pgwidgetdnd.obj" \
	"$(INTDIR)\pgwidgetlist.obj" \
	"$(INTDIR)\pgwidgetlistex.obj" \
	"$(INTDIR)\pgwindow.obj" \
	"$(INTDIR)\rendertextrect.obj" \
	"$(INTDIR)\theme_priv.obj" \
	"$(INTDIR)\themeloader.obj" \
	"$(INTDIR)\dir.obj" \
	"$(INTDIR)\grp.obj" \
	"$(INTDIR)\physfs.obj" \
	"$(INTDIR)\unzip.obj" \
	"$(INTDIR)\win32.obj" \
	"$(INTDIR)\zip.obj"

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
SOURCE=..\..\src\parastretch.cpp

"$(INTDIR)\parastretch.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgapplication.cpp

"$(INTDIR)\pgapplication.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgbutton.cpp

"$(INTDIR)\pgbutton.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgbuttongroup.cpp

"$(INTDIR)\pgbuttongroup.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgcheckbutton.cpp

"$(INTDIR)\pgcheckbutton.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgcolumnitem.cpp

"$(INTDIR)\pgcolumnitem.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgdrawline.cpp

"$(INTDIR)\pgdrawline.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgdrawobject.cpp

"$(INTDIR)\pgdrawobject.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgdropdown.cpp

"$(INTDIR)\pgdropdown.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgeventobject.cpp

"$(INTDIR)\pgeventobject.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgfile.cpp

"$(INTDIR)\pgfile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgfilearchive.cpp

"$(INTDIR)\pgfilearchive.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgfont.cpp

"$(INTDIR)\pgfont.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pggradientwidget.cpp

"$(INTDIR)\pggradientwidget.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgimage.cpp

"$(INTDIR)\pgimage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pglabel.cpp

"$(INTDIR)\pglabel.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pglayout.cpp

"$(INTDIR)\pglayout.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pglineedit.cpp

"$(INTDIR)\pglineedit.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pglistbox.cpp

"$(INTDIR)\pglistbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pglistboxbaseitem.cpp

"$(INTDIR)\pglistboxbaseitem.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pglistboxitem.cpp

"$(INTDIR)\pglistboxitem.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pglog.cpp

"$(INTDIR)\pglog.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgmaskedit.cpp

"$(INTDIR)\pgmaskedit.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgmessagebox.cpp

"$(INTDIR)\pgmessagebox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgmessageobject.cpp

"$(INTDIR)\pgmessageobject.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgmsgmap.cpp

"$(INTDIR)\pgmsgmap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgnavigator.cpp

"$(INTDIR)\pgnavigator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgpopupmenu.cpp

"$(INTDIR)\pgpopupmenu.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgprogressbar.cpp

"$(INTDIR)\pgprogressbar.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgradiobutton.cpp

"$(INTDIR)\pgradiobutton.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgrect.cpp

"$(INTDIR)\pgrect.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgrectlist.cpp

"$(INTDIR)\pgrectlist.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgrichedit.cpp

"$(INTDIR)\pgrichedit.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgrotozoom.cpp

"$(INTDIR)\pgrotozoom.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgscrollbar.cpp

"$(INTDIR)\pgscrollbar.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgslider.cpp

"$(INTDIR)\pgslider.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgspinnerbox.cpp

"$(INTDIR)\pgspinnerbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgstaticframe.cpp

"$(INTDIR)\pgstaticframe.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgsurfacecache.cpp

"$(INTDIR)\pgsurfacecache.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgwidget.cpp

"$(INTDIR)\pgwidget.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgwidgetdnd.cpp

"$(INTDIR)\pgwidgetdnd.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgwidgetlist.cpp

"$(INTDIR)\pgwidgetlist.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgwidgetlistex.cpp

"$(INTDIR)\pgwidgetlistex.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\pgwindow.cpp

"$(INTDIR)\pgwindow.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\rendertextrect.cpp

"$(INTDIR)\rendertextrect.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\themes\theme_priv.cpp

"$(INTDIR)\theme_priv.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\themes\themeloader.cpp

"$(INTDIR)\themeloader.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\physfs\archivers\dir.c

"$(INTDIR)\dir.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\physfs\archivers\grp.c

"$(INTDIR)\grp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\physfs\physfs.c

"$(INTDIR)\physfs.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\physfs\archivers\unzip.c

"$(INTDIR)\unzip.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\physfs\platform\win32.c

"$(INTDIR)\win32.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\physfs\archivers\zip.c

"$(INTDIR)\zip.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

