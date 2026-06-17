#include "debloat.hpp"
#include "cmd/exec.hpp"

namespace debloat
{
    string get_packages()
    {
        return exec("adb shell pm list packages");
    }

    string get_adb_devices()
    {
        return exec("adb devices");
    }
}