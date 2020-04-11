# Rocker

*Rocker* is a simple **C** code generator to handle *mustache-like* logicless templates.
The main goal is to handle all of the template engine aspects in compile-time, not runtime.

## Docker

To simplify work with *Rocker*, there is a *Dockerfile* in the root of project.

## Manual Building

To build, you will need *CMake* plus some compiler and toolchain installed.
Any of mainstream ones will do (e.g. *GCC*, *Clang*, *MSVC*).

After installing, use (in your favorite shell):

    mkdir release && cd release
    cmake -DCMAKE_BUILD_TYPE=Release ..
    cmake --build .

You will get *Rocker* executable file in *release* dir.
