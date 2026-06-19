cmake_minimum_required(VERSION 3.10)
project(debloating_tool)
enable_testing()
add_executable(debloat
    src/main.cpp
    src/cmd/exec.cpp
    src/debloat/debloat.cpp
    src/adb/adb.cpp
    src/util/util.cpp
)
add_executable(util_test
    src/util/util.cpp
    tests/util_test.cpp
)
add_test(NAME util_test COMMAND util_test)