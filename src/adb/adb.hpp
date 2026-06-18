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
        string serial;
        string state;
    };

    vector<Device> get_adb_devices();

    vector<Device> parse_adb_devices(const char *devices_string);
}