cmake_minimum_required(VERSION 3.10)
project(debloating_tool)
enable_testing()
add_executable(debloat
    src/main.cpp
    src/cmd/exec.cpp
    src/debloat/debloat.cpp
    src/adb/adb.cpp
    src/adb/package.cpp
    src/util/util.cpp
)
add_executable(util_test
    src/util/util.cpp
    tests/util_test.cpp
)
add_executable(adb_test
    src/adb/adb.cpp
    src/cmd/exec.cpp
    src/util/util.cpp
    tests/adb_test.cpp
)
add_test(NAME util_test COMMAND util_test)
add_test(NAME adb_test COMMAND adb_test)