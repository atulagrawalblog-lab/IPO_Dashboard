# IPO_Dashboard (Native Windows)

This repository contains a native Windows (Win32 + GDI+) application that calculates recommended IPO application sizes for Retail, Small HNI, and Big HNI categories.

## What’s included

- `main.cpp`, `UI.cpp`, `Logic.cpp`, `Theme.cpp`, `Settings.cpp` — source files
- `UI.h`, `Logic.h`, `Theme.h`, `Settings.h` — headers
- `Resources.rc`, `manifest.xml`, `app.ico` — resources
- `.github/workflows/windows-build.yml` — GitHub Actions CI to build `.exe`
- `build.bat` — local build script (MSVC or MinGW)
- `README.md` — this file

## Build locally (Windows)

### Using MSVC Build Tools (recommended)
1. Install **Build Tools for Visual Studio** (select "Desktop development with C++" and the Windows SDK).
2. Open "x64 Native Tools Command Prompt for VS".
3. Run:
   ```
   build.bat
   ```
   The script will compile resources, build `IPO_Dashboard.exe`, and launch it.

### Using MinGW (fallback)
1. Install MinGW-w64 and add `g++` to PATH.
2. Run:
   ```
   build.bat
   ```
   The script will attempt to build with `g++` and launch the app.

## Build on GitHub (Windows runner)

1. Push the repository to GitHub.
2. In the repository, go to **Actions** → **Build IPO Dashboard** → **Run workflow** (or push to `main`).
3. After the workflow completes, download the artifact `IPO_Dashboard` which contains `IPO_Dashboard.exe`.

## Notes
- The app follows the system light/dark theme automatically.
- The app uses Unicode APIs; source is compiled with `/DUNICODE /D_UNICODE`.
