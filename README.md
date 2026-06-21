# debloating_tool

A CLI tool for uninstalling, restoring, and installing Android applications through ADB without requiring root access.

## Overview

`debloating_tool` helps manage Android system applications using Android's built-in package manager. Applications are removed only for the current user, allowing them to be restored later without modifying the system partition.

## Features

* Uninstall system applications for the current user
* Restore previously removed system applications
* Install APK files from the local machine
* Read package names from command-line arguments or text files
* Prevent redundant operations by checking package state before execution
* Cross-platform support for Windows and Linux

## Requirements

* Android Debug Bridge (ADB)
* Android device with USB debugging enabled
* CMake 3.10 or later
* C++11 compatible compiler (GCC, Clang, or MSVC)

## Building

Clone the repository and build the project:

```bash
git clone https://github.com/tarun-ainampudi/debloating_tool.git
cd debloating_tool
cmake -S . -B build
cmake --build build
```

### Linux

Install the required packages:

```bash
sudo apt update
sudo apt install g++
sudo apt install cmake
sudo apt install adb
```

Build:

```bash
cmake -S . -B build
cmake --build build
```

### Windows

Install:

* Visual Studio with C++ workload or MinGW-w64
* CMake
* Android Platform Tools (ADB)

Verify installation:

```powershell
adb version
cmake --version
```

Build:

```powershell
cmake -S . -B build
cmake --build build
```

## Usage

```text
debloat -u -l <pkg1,pkg2,...>
debloat -u -f <packages.txt>
debloat -i -l <pkg1,pkg2,...>
debloat -i <app.apk>
```

### Options

| Option              | Description                              |
| ------------------- | ---------------------------------------- |
| `-u`, `--uninstall` | Uninstall packages                       |
| `-i`, `--install`   | Install APK or restore existing packages |
| `-v`, `--version`   | Display version information              |
| `-h`, `--help`      | Display help information                 |

### Input Methods

| Option         | Description                        |
| -------------- | ---------------------------------- |
| `-l`, `--list` | Comma-separated package list       |
| `-f`, `--file` | Text file containing package names |

## Examples

### Uninstall packages

```bash
debloat -u -l com.xyz.abc,in.def.uvw,org.rst.ghi
```

### Uninstall packages from a file

```bash
debloat -u -f bloatware_list.txt
```

Contents of `bloatware_list.txt`:

```text
com.xyz.abc
in.def.uvw
org.rst.ghi
```

### Restore a system application

```bash
debloat -i -l com.xyz.abc
```

### Install an APK

```bash
debloat -i my_app.apk
```

## Testing

Run the test suite:

```bash
cd build
ctest
```

## Notes

* ADB must detect the target device before running commands.
* Uninstall operations remove applications only for the current user.
* System partitions are not modified.
* Restored applications must already exist on the device as system packages.
* Review package names carefully before uninstalling applications.

## License

This project is licensed under the MIT License.
