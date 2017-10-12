@echo off
cd "./build"
@echo on

cmake -G "MinGW Makefiles" ..
"C:/MinGW/bin/mingw32-make.exe"

@echo off
cd "../"
@echo on

pause
