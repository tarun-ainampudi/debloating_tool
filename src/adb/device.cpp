#include <sstream>
#include <iostream>


#include "../util/util.hpp"
#include "../cmd/exec.hpp"
#include "device.hpp"


namespace adb
{

    vector<Device> parse_adb_devices(const char *devices_string)
    {
        vector<string> lines = util::split_string(devices_string, '\n');
        vector<Device> devices;

        for (size_t i = 0; i < lines.size(); i++)
        {
            string trimmed_line = util::trim_string(lines[i]);
            if (trimmed_line.empty() ||
                trimmed_line == "* daemon not running; starting now at tcp:5037" ||
                trimmed_line == "* daemon started successfully" ||
                trimmed_line == "List of devices attached")
                continue;

            std::istringstream iss(trimmed_line);

            Device device;

            if (!(iss >> device.Serial >> device.State))
            {
                cout << "[Error] Parsing Error at parse_adb_devices" << endl;
                cout << "[Debug] Line: " << trimmed_line << endl;
                continue;
            }

            devices.push_back(device);
        }

        return devices;
    }

    vector<Device> get_adb_devices()
    {
        string cmd_out = exec("adb devices");
        return adb::parse_adb_devices(cmd_out.c_str());
    }
}