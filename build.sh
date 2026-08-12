#!/usr/bin/env bash
# build.sh -- one clean build, same shape as the Lab 0 C++ scripts.
set -e
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
