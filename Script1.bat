@echo off
if %errorlevel% equ 0 (
    echo C:\Users\Оля\source\repos\prototip1\VFS.csv
    prototip1.exe
    ls $TMP
) else (
    pause
)