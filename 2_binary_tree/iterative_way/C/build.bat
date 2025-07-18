::	Building the application under Windows by
::	using mingw. Make sure you have installed
::	and configured mingw on your system.
::
::	author:		ITWorks4U
::	created:	July 16th, 2025
@echo off
setlocal

::	set variables for the script itself
set compiler=gcc.exe
set flags=-g3 -Wall -Iinclude
set source=source\\binary_tree.c source\\main.c
set target=binary_tree.exe

::	set arguments to call with that script
set "build=build"
set "clean=clean"

::	exactly only one argument is required for the script
if "%1" == "" (
	echo usage "build.bat build" or "build.bat clean"
	goto :eof 
)

if not "%2" == "" (
	echo Error: Too many arguments detected.
	goto :eof
)

::	handling expected arguments
if "%1" == "build" (
	call :building_application
	goto :eof
)

if "%1" == "clean" (
	call :clean_up
	goto :eof
)

::	any other single unknown argument left
echo Error: unknown argument "%1"
goto :eof

::	----------
::	functions
::	----------
::	build the application
:building_application
%compiler% %flags% %source% -o %target%
::	end of function

::	remove the executable file
::	stdout and stderr are moved to nul (is equal to /dev/null in Linux)
:clean_up
del %target% > nul 2>&1
::	end of function