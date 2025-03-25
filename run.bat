@echo off

cmake -G "MinGW Makefiles" -S . -B build/
mingw32-make -C build/
cd build
Tunes.exe                                                                                                                 