# Microsoft Developer Studio Generated NMAKE File, Based on test.dsp
!IF "$(CFG)" == ""
CFG=test - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. test - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "test - Win32 Release" && "$(CFG)" != "test - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "test.mak" CFG="test - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "test - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "test - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "test - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : "..\..\bin\test.exe"

!ELSE 

ALL : "paragui_dynamic - Win32 Release" "..\..\bin\test.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"paragui_dynamic - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\paratest.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "..\..\bin\test.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /vmg /GX /O2 /I "../../src" /I "../../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\test.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\test.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib sdl.lib paragui.lib freetype.lib sdlmain.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\test.pdb" /machine:I386 /out:"../../bin/test.exe" /libpath:"../../lib" 
LINK32_OBJS= \
	"$(INTDIR)\paratest.obj" \
	"..\..\lib\paragui.lib"

"..\..\bin\test.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

!IF "$(RECURSE)" == "0" 

ALL : "..\..\bin\testd.exe"

!ELSE 

ALL : "paragui_dynamic - Win32 Debug" "..\..\bin\testd.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"paragui_dynamic - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\paratest.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\testd.pdb"
	-@erase "..\..\bin\testd.exe"
	-@erase "..\..\bin\testd.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /Gm /vmg /GX /ZI /Od /I "../../src" /I "../../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\test.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\test.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib sdld.lib freetyped.lib paraguid.lib sdlmain.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\testd.pdb" /debug /machine:I386 /out:"../../bin/testd.exe" /pdbtype:sept /libpath:"../../lib" 
LINK32_OBJS= \
	"$(INTDIR)\paratest.obj" \
	"..\..\lib\paraguid.lib"

"..\..\bin\testd.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("test.dep")
!INCLUDE "test.dep"
!ELSE 
!MESSAGE Warning: cannot find "test.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "test - Win32 Release" || "$(CFG)" == "test - Win32 Debug"
SOURCE=..\..\test\paratest.cpp

"$(INTDIR)\paratest.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!IF  "$(CFG)" == "test - Win32 Release"

"paragui_dynamic - Win32 Release" : 
   cd "\projects\paragui\VisualC\paragui_dynamic"
   $(MAKE) /$(MAKEFLAGS) /F .\paragui_dynamic.mak CFG="paragui_dynamic - Win32 Release" 
   cd "..\test"

"paragui_dynamic - Win32 ReleaseCLEAN" : 
   cd "\projects\paragui\VisualC\paragui_dynamic"
   $(MAKE) /$(MAKEFLAGS) /F .\paragui_dynamic.mak CFG="paragui_dynamic - Win32 Release" RECURSE=1 CLEAN 
   cd "..\test"

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

"paragui_dynamic - Win32 Debug" : 
   cd "\projects\paragui\VisualC\paragui_dynamic"
   $(MAKE) /$(MAKEFLAGS) /F .\paragui_dynamic.mak CFG="paragui_dynamic - Win32 Debug" 
   cd "..\test"

"paragui_dynamic - Win32 DebugCLEAN" : 
   cd "\projects\paragui\VisualC\paragui_dynamic"
   $(MAKE) /$(MAKEFLAGS) /F .\paragui_dynamic.mak CFG="paragui_dynamic - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\test"

!ENDIF 


!ENDIF 

