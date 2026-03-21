#!/usr/bin/env bash

# SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
# SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
#
# SPDX-License-Identifier: MIT

echo "Configuring local Ninja build..."
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug

ln -sf build/compile_commands.json .
echo "Build configured. Run 'ninja -C build' to compile."
