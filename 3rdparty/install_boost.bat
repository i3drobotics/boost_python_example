@echo off

SETLOCAL
:: set working directory to script directory
SET initcwd=%cd%
SET scriptpath=%~dp0
cd %scriptpath:~0,-1%

:: url for downloading python
set url=https://netcologne.dl.sourceforge.net/project/boost/boost/1.66.0/boost_1_66_0.7z
:: output folder where download is placed
SET outputfolder="%cd%"
:: full output filepath
SET output="%outputfolder%\boost_1_66_0.7z"
:: set 7z directory (used for extracting 7z file from boost)
set z7path="C:\Program Files\7-Zip\7z"

:: download python from url
bitsadmin /transfer Boost_Download_Job /download /priority normal %url% %output%

:: install boost in current directory
echo Installing boost...
%z7path% x boost_1_66_0.7z
:: build boost
cd boost_1_66_0
::bootstrap
::bjam
cd ..

:: remove installer
del boost_1_66_0.7z

:: reset working directory
cd %initcwd%

ENDLOCAL