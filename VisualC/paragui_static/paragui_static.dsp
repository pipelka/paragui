# Microsoft Developer Studio Project File - Name="paragui_static" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=paragui_static - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "paragui_static.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "paragui_static.mak" CFG="paragui_static - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "paragui_static - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "paragui_static - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "paragui_static - Win32 Release MT" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "paragui_static - Win32 Debug MT" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "paragui_static - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /vmg /GX /O2 /I "../../src/physfs" /I "../../src/themes" /I "../../src" /I "../../include" /D "HAVE_SDLIMAGE" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "PHYSFS_SUPPORTS_ZIP" /YX /FD /c
# ADD BASE RSC /l 0x405 /d "NDEBUG"
# ADD RSC /l 0x405 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../lib/paraguis.lib"

!ELSEIF  "$(CFG)" == "paragui_static - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /vmg /GX /ZI /Od /I "../../src/physfs" /I "../../src/themes" /I "../../src" /I "../../include" /D "HAVE_SDLIMAGE" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "PHYSFS_SUPPORTS_ZIP" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x405 /d "_DEBUG"
# ADD RSC /l 0x405 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../lib/paraguisd.lib"

!ELSEIF  "$(CFG)" == "paragui_static - Win32 Release MT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMT"
# PROP BASE Intermediate_Dir "ReleaseMT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMT"
# PROP Intermediate_Dir "ReleaseMT"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /vmg /GX /O2 /I "../../src/physfs" /I "../../src/themes" /I "../../src" /I "../../include" /D "HAVE_SDLIMAGE" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "PHYSFS_SUPPORTS_ZIP" /YX /FD /c
# ADD BASE RSC /l 0x405 /d "NDEBUG"
# ADD RSC /l 0x405 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../lib/paraguimts.lib"

!ELSEIF  "$(CFG)" == "paragui_static - Win32 Debug MT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugMT"
# PROP BASE Intermediate_Dir "DebugMT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugMT"
# PROP Intermediate_Dir "DebugMT"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /vmg /GX /ZI /Od /I "../../src/physfs" /I "../../src/themes" /I "../../src" /I "../../include" /D "HAVE_SDLIMAGE" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "PHYSFS_SUPPORTS_ZIP" /YX /FD /GZ /c
# ADD BASE RSC /l 0x405 /d "_DEBUG"
# ADD RSC /l 0x405 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../lib/paraguimtsd.lib"

!ENDIF 

# Begin Target

# Name "paragui_static - Win32 Release"
# Name "paragui_static - Win32 Debug"
# Name "paragui_static - Win32 Release MT"
# Name "paragui_static - Win32 Debug MT"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "core"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\core\missing.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\core\pgapplication.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\core\pgcolors.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\core\pgdatacontainer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\core\pgeventobject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\core\pgfile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\core\pgfilearchive.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\core\pglog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\core\pgmain.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\core\pgmessageobject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\core\pgmsgmap.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\core\pgmsgmap.h
# End Source File
# Begin Source File

SOURCE=..\..\src\core\pgnavigator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\core\pgrectlist.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\core\pgsurfacecache.cpp
# End Source File
# End Group
# Begin Group "font"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\font\facecache.h
# End Source File
# Begin Source File

SOURCE=..\..\src\font\pgfont.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\font\pgfont_impl.cpp
# End Source File
# End Group
# Begin Group "draw"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\draw\drawline.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\draw\drawtile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\draw\gradient.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\draw\pgrect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\draw\rotozoom.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\draw\setpixel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\draw\stretch.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\draw\surface.cpp
# End Source File
# End Group
# Begin Group "physfs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\physfs\archivers\dir.c
# End Source File
# Begin Source File

SOURCE=..\..\src\physfs\physfs.c
# End Source File
# Begin Source File

SOURCE=..\..\src\physfs\physfs.h
# End Source File
# Begin Source File

SOURCE=..\..\src\physfs\physfs_internal.h
# End Source File
# Begin Source File

SOURCE=..\..\src\physfs\archivers\unzip.c
# End Source File
# Begin Source File

SOURCE=..\..\src\physfs\archivers\unzip.h
# End Source File
# Begin Source File

SOURCE=..\..\src\physfs\platform\win32.c
# End Source File
# Begin Source File

SOURCE=..\..\src\physfs\archivers\zip.c
# End Source File
# End Group
# Begin Group "widgets"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\widgets\pgbutton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\widgets\pgbuttongroup.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\widgets\pgcheckbutton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\widgets\pgcolumnitem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\widgets\pgdropdown.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\widgets\pgimage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\widgets\pglabel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\widgets\pglayout.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\widgets\pglineedit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\widgets\pglistbox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\widgets\pglistboxbaseitem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\widgets\pglistboxitem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\widgets\pgmaskedit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\widgets\pgmenubar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\widgets\pgmessagebox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\widgets\pgpopupmenu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\widgets\pgprogressbar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\widgets\pgradiobutton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\widgets\pgrichedit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\widgets\pgscrollbar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\widgets\pgslider.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\widgets\pgspinnerbox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\widgets\pgthemewidget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\widgets\pgwidget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\widgets\pgwidgetdnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\widgets\pgwidgetlist.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\widgets\pgwidgetlistex.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\widgets\pgwindow.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\src\paragui.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\include\paraconfig.h
# End Source File
# Begin Source File

SOURCE=..\..\include\paraconfig_win32.h
# End Source File
# Begin Source File

SOURCE=..\..\include\paragui.h
# End Source File
# Begin Source File

SOURCE=..\..\include\paragui_types.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgapplication.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgbutton.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgcheckbutton.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgcolors.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgcolumnitem.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgcompat.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgdatacontainer.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgdraw.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgdropdown.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgeventobject.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgfile.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgfilearchive.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgfont.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgimage.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pginfo.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pglabel.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pglayout.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pglineedit.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pglistbox.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pglistboxbaseitem.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pglistboxitem.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pglog.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgmaskedit.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgmenubar.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgmessagebox.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgmessageobject.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgnavigator.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgpopupmenu.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgprogressbar.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgradiobutton.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgrect.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgrectlist.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgrichedit.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgscrollbar.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgslider.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgspinnerbox.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgsurfacecache.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgtheme.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgthemewidget.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgwidget.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgwidgetdnd.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgwidgetlist.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgwidgetlistex.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgwindow.h
# End Source File
# End Group
# End Target
# End Project
