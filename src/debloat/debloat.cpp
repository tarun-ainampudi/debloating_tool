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

    void install_existing_pkgs(const unordered_set<string> &pkgs)
    {
        unordered_set<string> to_install = util::uset_intersection(get_all_packages(), pkgs);
        unordered_set<string> can_install = util::uset_difference(to_install, get_installed_packages());
        for (const string &pkg : pkgs)
        {
            if (can_install.find(pkg) != can_install.end())
                cout << "[Install Existing] " << pkg << ": " << install_existing(pkg);
            else
                cout << "[Install Existing] " << pkg << ": " << "Not Found or Already Installed\n";
        }
    }

    void install_existing_pkgs(const char *pkgs)
    {
        vector<string> pkgs_vec = util::split_string(pkgs, ',');

        unordered_set<string> pkgs_set(
            make_move_iterator(pkgs_vec.begin()),
            make_move_iterator(pkgs_vec.end()));

        install_existing_pkgs(pkgs_set);
    }

    void uninstall_packages(const unordered_set<string> &pkgs)
    {
        for (const string &pkg : pkgs)
        {
            cout << "[Uninstall] " << pkg << ": " << uninstall(pkg);
        }
    }

    void uninstall_packages(const char *pkgs)
    {
        vector<string> pkgs_vec = util::split_string(pkgs, ',');

        unordered_set<string> pkgs_set(
            make_move_iterator(pkgs_vec.begin()),
            make_move_iterator(pkgs_vec.end()));

        uninstall_packages(pkgs_set);
    }

}