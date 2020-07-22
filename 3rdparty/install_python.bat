@echo off

SETLOCAL
:: set working directory to script directory
SET initcwd=%cd%
SET scriptpath=%~dp0
cd %scriptpath:~0,-1%

:: url for downloading python
set url=https://www.python.org/ftp/python/3.5.0/python-3.5.0-amd64.exe
:: output folder where download is placed
SET outputfolder="%cd%"
:: full output filepath
SET output="%outputfolder%\python-3.5.0-amd64-installer.exe"

:: download python from url
bitsadmin /transfer Python_Download_Job /download /priority normal %url% %output%

:: install python in current directory
echo Installing python...
mkdir python-3.5
python-3.5.0-amd64-installer.exe /passive InstallAllUsers=0 TargetDir=%outputfolder%\python-3.5 Shortcuts=0 Include_doc=0 Include_launcher=0 InstallLauncherAllUsers=0 Include_test=0 SimpleInstall=1 SimpleInstallDescription="Install python"
:: remove installer
del python-3.5.0-amd64-installer.exe

:: upgrade pip
python-3.5\python -m pip install --upgrade pip
:: upgrade setuptools
python-3.5\python -m pip install --upgrade setuptools 
:: install required module with requirements.txt
python-3.5\python -m pip install -r requirements.txt

:: reset working directory
cd %initcwd%

ENDLOCAL