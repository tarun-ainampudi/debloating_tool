#include <sstream>
#include <iostream>

#include "debloat.hpp"
#include "../cmd/exec.hpp"
#include "../util/util.hpp"

namespace debloat
{
    string modify_package(const string &cmd, const string &pkg_name)
    {
        return exec((cmd + " " + pkg_name).c_str());
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

    void install_existing_pkgs(const char *pkgs)
    {
        unordered_set<string> uninstalled = get_uninstalled_packages();
        vector<string> should_install = util::split_string(pkgs, ',');
        for (size_t i = 0; i < should_install.size(); i++)
        {
            if (uninstalled.contains(should_install[i]))
            {
                cout << install_existing(should_install[i]) << endl;
            }
            else
            {
                cout << "[Install-Existing] [Not Found] " << should_install[i] << endl;
            }
        }
    }

    void uninstall_packages(const char *pkgs)
    {
        unordered_set<string> enabled = get_enabled_packages();
        vector<string> should_uninstall = util::split_string(pkgs, ',');
        for (size_t i = 0; i < should_uninstall.size(); i++)
        {
            if (enabled.contains(should_uninstall[i]))
            {
                cout << "[Uninstall] " << should_uninstall[i] << endl;
                cout << uninstall(should_uninstall[i]) << endl;
            }
            else
            {
                cout << "[Uninstall] [Not Found] " << should_uninstall[i] << endl;
            }
        }
    }

}