cmake_minimum_required(VERSION 3.10)
project(debloating_tool)
add_executable(debloat
    src/main.cpp
    src/cmd/exec.cpp
    src/debloat/debloat.cpp
    src/adb/adb.cpp
    src/util/util.cpp
)
