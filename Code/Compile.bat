@echo off
if not defined DevEnvDir (
	call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
)
if not defined DevEnvDir (
	call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
)

set FILES=..\Code\main.cpp

set LIBS=opengl32.lib kernel32.lib user32.lib gdi32.lib


IF NOT EXIST ..\bin mkdir ..\bin
pushd ..\bin
cl /MT /nologo /W3 /Z7 /GS- /Gs999999 /O2  /arch:AVX2 /std:c++20 /DMAIN_DEBUG=0 %FILES% -Fe..\bin\TheButton.exe %LIBS% /link /incremental:no /opt:icf /opt:ref /subsystem:windows
cl /MTd /nologo /W3 /Z7 /GS- /Gs999999 /arch:AVX2 /std:c++20 /DMAIN_DEBUG=1 %FILES% -Fe..\bin\TheButtonDebug.exe %LIBS% /link /incremental:no /opt:icf /opt:ref /subsystem:console
popd