set include=c:\projetcs\include;c:\projects\include\SDL;%include%
set lib=c:\projects\lib;c:\projects\lib\SDL;%lib%

cd VisualC

cd paragui_dynamic
NMAKE /f "paragui_dynamic.mak" CFG="paragui_dynamic - Win32 Release"
cd ..

cd test
NMAKE /f "test.mak" CFG="test - Win32 Release"
cd ..

cd ..

rem rd /S /Q paragui-win32

mkdir paragui-win32
mkdir paragui-win32\bin
mkdir paragui-win32\lib
mkdir paragui-win32\include
mkdir paragui-win32\data

copy bin\paragui.dll paragui-win32\bin
copy bin\test.exe paragui-win32\bin

copy include\*.h paragui-win32\include
copy lib\paragui.lib paragui-win32\lib

copy README paragui-win32
copy README-ParaGUI.txt paragui-win32
copy RELEASENOTES.final paragui-win32
copy COPYING paragui-win32
copy CREDITS paragui-win32

copy data\default.zip paragui-win32\data
copy data\simple.zip paragui-win32\data
