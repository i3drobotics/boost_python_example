@echo off

SETLOCAL
:: set working directory to script directory
SET initcwd=%cd%
SET scriptpath=%~dp0
cd %scriptpath:~0,-1%

:: install boost
call ..\3rdparty\install_boost.bat

:: install python
call ..\3rdparty\install_python.bat

:: reset working directory
cd %initcwd%

:: complete message
echo 3rdparty install complete.
pause

ENDLOCAL