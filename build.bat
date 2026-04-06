REM SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
REM SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
REM
REM SPDX-License-Identifier: MIT

@echo off

REM Use setlocal so we don't permanently alter the user's terminal environment
setlocal

set "CMAKE_EXE=cmake"

where cmake >nul 2>nul
if %errorlevel% neq 0 (
    echo CMake not found in PATH. Searching for common installation directories...

    if exist "C:\Program Files\CMake\bin\cmake.exe" (
        set "CMAKE_EXE=C:\Program Files\CMake\bin\cmake.exe"
    ) else if exist "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" (
        set "CMAKE_EXE=C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"
    ) else if exist "C:\Program Files\Microsoft Visual Studio\2022\Professional\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" (
        set "CMAKE_EXE=C:\Program Files\Microsoft Visual Studio\2022\Professional\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"
    ) else if exist "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" (
        set "CMAKE_EXE=C:\Program Files\Microsoft Visual Studio\2022\Enterprise\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"
    ) else (
        echo.
        echo [ERROR] CMake could not be found anywhere.
        echo Please install CMake from cmake.org or ensure the "C++ CMake tools for Windows"
        echo component is installed via the Visual Studio Installer.
        pause
        exit /b 1
    )
)

echo Using CMake at: "%CMAKE_EXE%"
echo.


echo Generating Visual Studio 2022 Solution for submission...
"%CMAKE_EXE%" -S . -B vs_build -G "Visual Studio 17 2022"
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] CMake failed to generate the project files.
    pause
    exit /b %errorlevel%
)


echo.
echo Building solution for Release...
"%CMAKE_EXE%" --build vs_build --config Release
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] The build process failed.
    pause
    exit /b %errorlevel%
)

echo.
echo vs_build\DeadMansDrawPlusPlus.sln should now be ready. You can open this in Visual Studio.
pause
