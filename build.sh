#!/usr/bin/env bash

# SPDX-FileCopyrightText: 2026 Claire Tam <claire.tam@student.adelaide.edu.au>
# SPDX-FileCopyrightText: 2026 fractuscontext (aka Claire T.) <106440141+fractuscontext@users.noreply.github.com>
#
# SPDX-License-Identifier: MIT

set -euo pipefail

BUILD_DIR="build"
COVERAGE_DIR="coverage_report"

configure() {
    local extra_flags="${1:-}"
    cmake -S . -B "$BUILD_DIR" -G Ninja -DCMAKE_BUILD_TYPE=Debug \
        -DCMAKE_CXX_FLAGS="-Wall -Wextra -Wpedantic $extra_flags"
    cmake --build "$BUILD_DIR"
    ln -sf "$BUILD_DIR/compile_commands.json" .
}

usage() {
    cat <<EOF
Usage: ./build.sh [COMMAND]

Commands:
  (none)      Build and run the game with AddressSanitizer
  test        Build and run unit tests with AddressSanitizer
  coverage    Build, run tests, and generate an HTML coverage report

Examples:
  ./build.sh              # play the game
  ./build.sh test         # run tests
  ./build.sh coverage     # generate coverage report
EOF
}


cmd_run() {
    echo "==> Building (AddressSanitizer enabled)..."
    configure "-fsanitize=address -g"
    echo ""
    echo "==> Running game..."
    ./"$BUILD_DIR"/DeadMansDrawPlusPlus
}

cmd_test() {
    echo "==> Building tests (AddressSanitizer enabled)..."
    configure "-fsanitize=address -g"
    echo ""
    echo "==> Running tests..."
    ./"$BUILD_DIR"/DeadMansDrawTests
}

cmd_coverage() {
    echo "==> Building with coverage instrumentation..."
    configure "-fprofile-instr-generate -fcoverage-mapping"
    echo ""

    echo "==> Running tests..."
    LLVM_PROFILE_FILE="$BUILD_DIR/coverage.profraw" ./"$BUILD_DIR"/DeadMansDrawTests
    echo ""

    echo "==> Generating coverage report..."
    llvm-profdata merge -sparse "$BUILD_DIR/coverage.profraw" \
        -o "$BUILD_DIR/coverage.profdata"

    llvm-cov report ./"$BUILD_DIR"/DeadMansDrawTests \
        -instr-profile="$BUILD_DIR/coverage.profdata" \
        -ignore-filename-regex='(googletest|_deps|tests/)'

    llvm-cov show ./"$BUILD_DIR"/DeadMansDrawTests \
        -instr-profile="$BUILD_DIR/coverage.profdata" \
        --format=html -output-dir="$COVERAGE_DIR" \
        -ignore-filename-regex='(googletest|_deps|tests/)'

    echo ""
    echo "==> HTML report: $COVERAGE_DIR/index.html"
}

case "${1:-}" in
    test)       cmd_test ;;
    coverage)   cmd_coverage ;;
    help|-h)    usage ;;
    "")         cmd_run ;;
    *)          echo "Unknown command: $1" >&2; usage >&2; exit 1 ;;
esac
