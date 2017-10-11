@echo off
cd "./build"
@echo on

cmake -G "MinGW Makefiles" ..
mingw32-make

@echo off
cd "../"
@echo on

pause
