@echo off
REM build.bat - builds IPO_Dashboard.exe using MSVC Build Tools if available, otherwise tries MinGW

set EXE_NAME=IPO_Dashboard.exe

REM Check for MSVC environment by looking for cl.exe in PATH
where cl >nul 2>nul
if %ERRORLEVEL% == 0 (
    echo Found MSVC (cl). Building with MSVC...
    rc /fo Resources.res Resources.rc
    cl /DUNICODE /D_UNICODE main.cpp UI.cpp Logic.cpp Theme.cpp Settings.cpp Resources.res /Fe:%EXE_NAME% /link gdiplus.lib comctl32.lib
    if %ERRORLEVEL% == 0 (
        echo Build succeeded.
        start "" "%EXE_NAME%"
        exit /b 0
    ) else (
        echo MSVC build failed.
    )
) 

REM Try MinGW g++
where g++ >nul 2>nul
if %ERRORLEVEL% == 0 (
    echo Found g++. Building with MinGW...
    g++ -municode main.cpp UI.cpp Logic.cpp Theme.cpp Settings.cpp -o %EXE_NAME% -lgdi32 -lcomctl32
    if %ERRORLEVEL% == 0 (
        echo Build succeeded.
        start "" "%EXE_NAME%"
        exit /b 0
    ) else (
        echo MinGW build failed.
    )
)

echo No supported compiler found in PATH. Install MSVC Build Tools or MinGW and re-run build.bat.
pause
