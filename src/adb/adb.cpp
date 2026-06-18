#include <sstream>

#include "adb.hpp"
#include "../cmd/exec.hpp"

namespace adb
{

    vector<Device> get_adb_devices()
    {
        string cmd_out = exec("adb devices");
        return adb::parse_adb_devices(cmd_out.c_str());
    }

    vector<Device> parse_adb_devices(const char *devices_string)
    {
        vector<string> lines = util::split_string(devices_string, '\n');
        vector<Device> devices;

        for (size_t i = 1; i < lines.size(); i++)
        {
            if (util::trim_string(lines[i]).empty())
                continue;

            std::istringstream iss(lines[i]);

            Device device;

            if (!(iss >> device.serial >> device.state))
            {
                cout << "[Error] Parsing Error at parse_adb_devices\n";
                cout << "[Debug] Line: " << lines[i] << endl;
                continue;
            }

            devices.push_back(device);
        }

        return devices;
    }

}
