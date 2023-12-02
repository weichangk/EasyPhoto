@echo off
setlocal EnableDelayedExpansion

set "folder=%~dp0\..\%1"

SETLOCAL ENABLEDELAYEDEXPANSION

for /r "%folder%" %%f in (*.h *.hpp) do (
  set "headers=!headers!%%~ff "
)

for /r "%folder%" %%f in (*.cpp *.cc) do (
  set "srcs=!srcs!%%~ff "
)

set "outfolder=%~dp0\..\%1\lang"
if not exist "%outfolder%" (
    mkdir "%outfolder%"
)

if "%2"=="" (
for /r "%folder%" %%f in (*.ts) do (
  echo lupdate %%~nxf
  lupdate -recursive !headers! !srcs! -ts %outfolder%\%%~nxf
)
) else (
	echo lupdate %1_%2.ts
	lupdate -recursive !headers! !srcs! -ts %outfolder%\%1_%2.ts
)

pause
