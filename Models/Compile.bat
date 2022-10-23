@echo off
if not defined DevEnvDir (
	call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
)

set FILES=ModelBaker.cpp

set LIBS=kernel32.lib user32.lib gdi32.lib

cl /EHsc /MTd /nologo /W3 /Z7 /GS- /Gs999999 /arch:AVX2 /std:c++latest %FILES% -FeModelBaker.exe %LIBS% /link /incremental:no /opt:icf /opt:ref /subsystem:console