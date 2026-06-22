#pragma once

#include <string>

using namespace std;

namespace adb
{
    string modify_package(const string &cmd, const string &pkg_name);

    string uninstall(const string &pkg);

    string install(const string &pkg);

    string install_existing(const string &pkg);

    string disable(const string &pkg);

    string suspend(const string &pkg);
}