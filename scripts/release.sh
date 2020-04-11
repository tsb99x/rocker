#!/bin/sh

mkdir /build && cd /build
cmake -GNinja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_EXE_LINKER_FLAGS="-static" \
    /app
cmake --build . --target rocker

mkdir -p /app/release
cp /build/rocker /app/release
