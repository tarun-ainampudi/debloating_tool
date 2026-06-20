#include <sstream>

#include "../cmd/exec.hpp"
#include "../util/util.hpp"
#include "package.hpp"

namespace adb
{
    unordered_set<string> get_packages(const char *cmd)
    {
        string cmd_out = exec(cmd);
        unordered_set<string> packages;
        istringstream iss(cmd_out);
        string temp;
        while (getline(iss, temp))
        {
            packages.insert(temp.substr(8));
        }
        return packages;
    }

    unordered_set<string> get_all_packages()
    {
        return get_packages("adb shell pm list packages -u");
    }

    unordered_set<string> get_enabled_packages()
    {
        return get_packages("adb shell pm list packages -e");
    }

    unordered_set<string> get_installed_packages()
    {
        return get_packages("adb shell pm list packages");
    }

    unordered_set<string> get_uninstalled_packages()
    {
        return util::uset_difference(get_all_packages(), get_installed_packages());
    }
}