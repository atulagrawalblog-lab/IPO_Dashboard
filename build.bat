@echo off
setlocal

REM ===============================
REM IPO Dashboard Local Build Script
REM ===============================

REM Compile resources (icon + manifest)
rc /fo Resources.res Resources.rc
if errorlevel 1 (
    echo Resource compilation failed.
    pause
    exit /b 1
)

REM Compile and link (Unicode + required Windows libs)
cl /DUNICODE /D_UNICODE main.cpp UI.cpp Logic.cpp Theme.cpp Settings.cpp Resources.res ^
/Fe:IPO_Dashboard.exe ^
/link user32.lib gdi32.lib comctl32.lib gdiplus.lib advapi32.lib ole32.lib
if errorlevel 1 (
    echo Build failed.
    pause
    exit /b 1
)

REM Launch the application
if exist IPO_Dashboard.exe (
    echo Build successful! Launching IPO_Dashboard.exe...
    start "" IPO_Dashboard.exe
) else (
    echo EXE not found after build.
)

endlocal
