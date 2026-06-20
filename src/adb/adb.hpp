#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "../util/util.hpp"

using namespace std;

namespace adb
{
    struct Device
    {
        string Serial;
        string State;
    };

    vector<Device> parse_adb_devices(const char *devices_string);

    vector<Device> get_adb_devices();

    string modify_package(const string &cmd, const string &pkg_name);

    string uninstall(const string &pkg);

    string install_existing(const string &pkg);

    string disable(const string &pkg);

    string suspend(const string &pkg);
}