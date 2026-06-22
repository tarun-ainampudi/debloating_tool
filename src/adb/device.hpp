#pragma once

#include <string>
#include <vector>

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
}