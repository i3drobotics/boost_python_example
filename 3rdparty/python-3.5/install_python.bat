@echo off

SETLOCAL
:: set working directory to script directory
SET initcwd=%cd%
SET scriptpath=%~dp0
cd %scriptpath:~0,-1%

SET python_version=3.5.0

:: download file
SET downloadfile=python-%python_version%-amd64.exe
:: url for downloading python
set url=https://www.python.org/ftp/python/%python_version%/%downloadfile%
:: output folder where download is placed
SET downloadfolder="%cd%"
:: full output filepath
SET downloadpath=%downloadfolder%\%downloadfile%

:: download python from url
curl -o "%downloadpath%" -L %url%

:: install python in current directory
echo Installing python...
mkdir python
%downloadfile% /passive InstallAllUsers=0 TargetDir=%downloadfolder%\python Shortcuts=0 Include_doc=0 Include_launcher=0 InstallLauncherAllUsers=0 Include_test=0 SimpleInstall=1 SimpleInstallDescription="Install python"
:: remove installer
del %downloadfile%

:: upgrade pip
python\python -m pip install --upgrade pip
:: upgrade setuptools
python\python -m pip install --upgrade setuptools 
:: install required module with requirements.txt
python\python -m pip install -r requirements.txt

:: reset working directory
cd %initcwd%

ENDLOCAL