@echo off

SETLOCAL
:: set working directory to script directory
SET initcwd=%cd%
SET scriptpath=%~dp0
cd %scriptpath:~0,-1%

:: install python
call ..\3rdparty\python-3.5\install_python.bat

:: install boost
call ..\3rdparty\boost-1.66.0\install_boost_python.bat

:: reset working directory
cd %initcwd%

:: complete message
echo 3rdparty install complete.

ENDLOCAL