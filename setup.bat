REM SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
REM SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
REM
REM SPDX-License-Identifier: MIT

@echo off
echo Generating Visual Studio 2022 Solution for submission...
cmake -S . -B vs_build -G "Visual Studio 17 2022"
echo Done. You can now zip the vs_build directory or open vs_build\DeadMansDrawPlusPlus.sln
pause
