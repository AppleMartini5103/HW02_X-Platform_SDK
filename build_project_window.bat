@echo off
setlocal

echo ========================================
echo RADAR Verification Tool - Build Script
echo ========================================
echo.

REM ================
REM  VS Environment
REM ================
echo [0/3] Setting up Visual Studio environment...

REM Try vswhere to locate vcvarsall.bat automatically
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%VSWHERE%" set "VSWHERE=%ProgramFiles%\Microsoft Visual Studio\Installer\vswhere.exe"

if exist "%VSWHERE%" (
    for /f "usebackq tokens=*" %%i in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do (
        set "VS_INSTALL_DIR=%%i"
    )
)

if defined VS_INSTALL_DIR (
    set "VCVARSALL=%VS_INSTALL_DIR%\VC\Auxiliary\Build\vcvarsall.bat"
    if exist "%VCVARSALL%" (
        call "%VCVARSALL%" x64
        echo [OK] Visual Studio environment initialized
    ) else (
        echo [WARN] vcvarsall.bat not found, assuming environment is already set up
    )
) else (
    echo [WARN] Visual Studio not found via vswhere, assuming environment is already set up
)
echo.

REM ================
REM      Clear
REM ================
echo [1/3] Cleaning build directory...
if exist build (
    rmdir /s /q build
    if errorlevel 1 (
        echo [ERROR] Failed to delete build directory
        pause
        exit /b 1
    )
    echo [OK] Build directory cleaned
) else (
    echo [INFO] Build directory does not exist, skipping clean
)
echo.

REM ================
REM      Configure
REM ================
echo [2/3] Configuring with CMake...
cmake -B build -G "Visual Studio 17 2022" -A x64
if errorlevel 1 (
    echo.
    echo [ERROR] CMake configuration failed!
    echo.
    echo Please check:
    echo   1. CMake is installed and in PATH
    echo   2. You are running from "Developer Command Prompt for VS"
    echo   3. All required libraries are in 3rdparty/
    echo.
    pause
    exit /b 1
)
echo [OK] Configuration successful
echo.

REM ================
REM      Build
REM ================
echo [3/3] Building project...
cmake --build build
if errorlevel 1 (
    echo.
    echo [ERROR] Build failed!
    echo.
    echo Please check the error messages above.
    echo.
    pause
    exit /b 1
)
echo [OK] Build successful
echo.

REM ================
REM      Summary
REM ================
echo ========================================
echo Build completed successfully!
echo ========================================
echo.
echo Output: build\XPLATFORM_SDK.dll
echo Import: build\XPLATFORM_SDK.lib
echo.
echo [INFO] This is a shared library (DLL).
echo [INFO] Link XPLATFORM_SDK.lib and distribute XPLATFORM_SDK.dll with your application.
echo.