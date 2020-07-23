@echo off

SETLOCAL
:: set working directory to script directory
SET initcwd=%cd%
SET scriptpath=%~dp0
cd %scriptpath:~0,-1%

cd ../

:: make build & install folders
mkdir build
mkdir install
:: build library
cd build
cmake -G "Visual Studio 14 2015 Win64" -DCMAKE_INSTALL_PREFIX="../install/" ..
:: install library
cmake --build . --config Release --target install

:: reset working directory
cd %initcwd%

:: complete message
echo Build complete.