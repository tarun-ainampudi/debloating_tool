#pragma once

#include <string>
#include <vector>
#include "../util/util.hpp"

using namespace std;

namespace parser
{
    vector<string> parse_adb_devices(const char *devices_string);
}