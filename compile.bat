@echo off
echo // g++ src\*.cpp -o nachosconsole.exe -static-libstdc++ -static-libgcc
g++ src\*.cpp -o nachosconsole.exe -static-libstdc++ -static-libgcc
timeout 2 >nul

