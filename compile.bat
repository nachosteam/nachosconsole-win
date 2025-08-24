@echo off
echo // windres src\icon\icon.rc -O coff -o icon_res.o
windres src\icon\icon.rc -O coff -o icon_res.o
echo // g++ src\*.cpp icon_res.o -o nachosconsole.exe -static-libstdc++ -static-libgcc
g++ src\*.cpp icon_res.o -o nachosconsole.exe -static-libstdc++ -static-libgcc
echo // del icon_res.o
del icon_res.o
timeout 2 >nul

