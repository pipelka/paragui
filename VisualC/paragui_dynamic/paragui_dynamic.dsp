# Microsoft Developer Studio Project File - Name="paragui_dynamic" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=paragui_dynamic - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "paragui_dynamic.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "paragui_dynamic.mak" CFG="paragui_dynamic - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "paragui_dynamic - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "paragui_dynamic - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "paragui_dynamic - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PARAGUI_DYNAMIC_EXPORTS" /YX /FD /c
# ADD CPP /nologo /G5 /MD /W3 /vmg /GX /O1 /I "../../src/expat" /I "../../src/physfs" /I "../../src/themes" /I "../../src/core" /I "../../include" /D "ZLIB_DLL" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PARAGUI_EXPORTS" /D "PHYSFS_SUPPORTS_ZIP" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x405 /d "NDEBUG"
# ADD RSC /l 0x405 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 advapi32.lib sdl.lib freetype.lib sdl_image.lib physfs.lib /nologo /dll /machine:I386 /out:"../../bin/paragui.dll" /implib:"../../lib/paragui.lib" /libpath:"../../lib" /libpath:"../../src/physfs/Release"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Copying PhysFS DLL ...
PostBuild_Cmds=copy ..\..\src\physfs\Release\physfs.dll ..\..\bin
# End Special Build Tool

!ELSEIF  "$(CFG)" == "paragui_dynamic - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PARAGUI_DYNAMIC_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /vmg /GX /ZI /Od /I "../../src/expat" /I "../../src/physfs" /I "../../src/core" /I "../../include" /I "../../src/themes" /D "ZLIB_DLL" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PARAGUI_DYNAMIC_EXPORTS" /D "PHYSFS_SUPPORTS_ZIP" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x405 /d "_DEBUG"
# ADD RSC /l 0x405 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 advapi32.lib sdl.lib freetype.lib sdl_image.lib physfs.lib /nologo /dll /debug /machine:I386 /out:"../../bin/paraguid.dll" /implib:"../../lib/paraguid.lib" /pdbtype:sept /libpath:"../../lib" /libpath:"../../src/physfs/Debug"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Copying PhysFS DLL ...
PostBuild_Cmds=copy ..\..\src\physfs\Debug\physfs.dll ..\..\bin
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "paragui_dynamic - Win32 Release"
# Name "paragui_dynamic - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "themes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\themes\theme_priv.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\themes\theme_priv.h
# End Source File
# Begin Source File

SOURCE=..\..\src\themes\themeloader.cpp
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

SOURCE=..\..\src\core\pgmsgmap.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\core\pgnavigator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\core\pgsurfacecache.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\core\pgtimerobject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\core\physfsrwops.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\core\physfsrwops.h
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
# Begin Group "widgets"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\widgets\pgbutton.cpp
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

SOURCE=..\..\src\core\pgmessageobject.cpp
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

SOURCE=..\..\src\core\pgrectlist.cpp
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
# Begin Group "expat"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\expat\ascii.h
# End Source File
# Begin Source File

SOURCE=..\..\src\expat\asciitab.h
# End Source File
# Begin Source File

SOURCE=..\..\src\expat\expat.h
# End Source File
# Begin Source File

SOURCE=..\..\src\expat\iasciitab.h
# End Source File
# Begin Source File

SOURCE=..\..\src\expat\latin1tab.h
# End Source File
# Begin Source File

SOURCE=..\..\src\expat\nametab.h
# End Source File
# Begin Source File

SOURCE=..\..\src\expat\utf8tab.h
# End Source File
# Begin Source File

SOURCE=..\..\src\expat\xmldef.h
# End Source File
# Begin Source File

SOURCE=..\..\src\expat\xmlparse.c
# End Source File
# Begin Source File

SOURCE=..\..\src\expat\xmlparse.h
# End Source File
# Begin Source File

SOURCE=..\..\src\expat\xmlrole.c
# End Source File
# Begin Source File

SOURCE=..\..\src\expat\xmlrole.h
# End Source File
# Begin Source File

SOURCE=..\..\src\expat\xmltchar.h
# End Source File
# Begin Source File

SOURCE=..\..\src\expat\xmltok.c
# End Source File
# Begin Source File

SOURCE=..\..\src\expat\xmltok.h
# End Source File
# Begin Source File

SOURCE=..\..\src\expat\xmltok_impl.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\src\paragui.cpp
# End Source File
# Begin Source File

SOURCE=.\Version.rc
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

SOURCE=..\..\include\pgcolors.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pgcolumnitem.h
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

SOURCE=..\..\include\pgtimerobject.h
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
# Begin Source File

SOURCE=.\resource.h
# End Source File
# End Group
# End Target
# End Project
