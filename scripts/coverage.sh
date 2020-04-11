#!/bin/sh

mkdir /build && cd /build
cmake -GNinja \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_C_FLAGS="--coverage" \
    /app
cmake --build .
ctest

mkdir -p /app/coverage
gcovr -r /app/src --html --html-details -o /app/coverage/index.html -e ".*_test.c" \
    ./CMakeFiles/string_utils_test.dir/src \
    ./CMakeFiles/printer_test.dir/src
