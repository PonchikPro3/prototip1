@echo off
g++ -o prototip1.exe prototip1.cpp

if %errorlevel% equ 0 (
    prototip1.exe
) else (
    pause
)