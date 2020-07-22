@echo off

SETLOCAL
:: set working directory to script directory
SET initcwd=%cd%
SET scriptpath=%~dp0
cd %scriptpath:~0,-1%

set boost_version=1.66.0
SET "boost_version_=%boost_version:.=_%"

SET path_python=%scriptpath:~0,-1%\..\python-3.5\python
SET "path_python=%path_python:\=/%"

echo Downloading boost...
:: download file
SET downloadfile=boost_%boost_version_%.tar.gz
:: url for downloading boost
set url=https://sourceforge.net/projects/boost/files/boost/%boost_version%/%downloadfile%/download
:: folder where download is placed
SET downloadfolder=%cd%
:: full output filepath
SET downloadpath=%downloadfolder%\%downloadfile%

:: download python from url
curl -o "%downloadpath%" -L %url%

echo Boost download complete.

:: install boost in current directory
echo Extracting boost...
tar -xf %downloadfile%

echo Boost extraction complete.

echo Setting up boost

:: setup boost python config
cd boost_%boost_version_%
cmd /c bootstrap
cd ..
:: edit boost-python-config.jam file based on file location
CALL :edit_line "boost-python-config.jam", 4 , ": %path_python%/python.exe  # Interpreter"
CALL :edit_line "boost-python-config.jam", 5 , ": %path_python%/include  # Interpreter"
CALL :edit_line "boost-python-config.jam", 6 , ": %path_python%/libs  # Interpreter"

echo Boost python setup complete

echo Building boost python
:: build python
cd boost_%boost_version_%
.\b2 --with-python --toolset=msvc-14.0 architecture=x86 address-model=64 link=shared --user-config=..\boost-python-config.jam

echo Boost python build complete
cd ..

:: remove installer
del %downloadfile%

:: reset working directory
cd %initcwd%

EXIT /B %ERRORLEVEL%

:edit_line
set InputFile=%~1
set OutputFile=%InputFile%.tmp
set insertline=%~2
set newline=%~3
(for /f "tokens=1* delims=[]" %%a in ('find /n /v "##" ^< "%InputFile%"') do (
    if "%%~a"=="%insertline%" (
        echo %newline%
        REM ECHO.%%b
    ) ELSE (
        echo.%%b
    )
)) > %OutputFile%
::overwrite input with temp
copy /y %OutputFile% %InputFile%
del %OutputFile%
EXIT /B 0