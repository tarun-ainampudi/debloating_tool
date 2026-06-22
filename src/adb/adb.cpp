#include "adb.hpp"
#include "../cmd/exec.hpp"

namespace adb
{

    string modify_package(const string &cmd, const string &pkg_name)
    {
        return exec((cmd + " " + pkg_name).c_str());
    }

    string install(const string &pkg)
    {
        return exec(
            (string("adb install \"") + pkg + "\"").c_str());
    }

    string uninstall(const string &pkg)
    {
        return modify_package("adb shell pm uninstall --user current", pkg);
    }

    string install_existing(const string &pkg)
    {
        return modify_package("adb shell pm install-existing --user current", pkg);
    }

    string disable(const string &pkg)
    {
        return modify_package("adb shell pm disable-user --user current", pkg);
    }

    string suspend(const string &pkg)
    {
        return modify_package("adb shell pm suspend --user current", pkg);
    }

}
