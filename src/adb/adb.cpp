#include "adb.hpp"

namespace adb
{
    vector<string> parse_adb_devices(const char *devices_string)
    {
        return util::split_string(devices_string,' ');
    }

}
