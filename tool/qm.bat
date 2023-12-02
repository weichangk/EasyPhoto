@echo off
setlocal EnableDelayedExpansion

set "folder=%~dp0\..\%1\lang"
set "debug=%~dp0\..\bin\x64\Debug\lang\%2"
set "release=%~dp0\..\bin\x64\Release\lang\%2"
set "res=%~dp0\..\%1\res\lang\%2"

cd %folder%

if "%2"=="" (
	for /r "%folder%" %%f in (*.ts) do (
	  echo lrelease %%~nxf
	  lrelease %%~nxf %%nf.qm
	)
) else (
	echo lrelease %1_%2.ts
	lrelease %1_%2.ts %1_%2.qm

	if not exist "%debug%" (
		mkdir "%debug%"
	)
	if not exist "%release%" (
		mkdir "%release%"
	)
	if not exist "%res%" (
		mkdir "%res%"
	)

	copy /B %1_%2.qm %debug%\%1_%2.qm
	copy /B %1_%2.qm %release%\%1_%2.qm
	copy /B %1_%2.qm %res%\%1_%2.qm

	del %1_%2.qm
)

pause
