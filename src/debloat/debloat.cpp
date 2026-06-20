#include <iostream>

#include "debloat.hpp"
#include "../util/util.hpp"
#include "../adb/adb.hpp"
#include "../adb/package.hpp"

namespace debloat
{

    void install_existing_pkgs(const unordered_set<string> &pkgs)
    {
        unordered_set<string> to_install =
            util::uset_intersection(adb::get_all_packages(), pkgs);
        unordered_set<string> can_install =
            util::uset_difference(to_install, adb::get_installed_packages());
        for (const string &pkg : pkgs)
        {
            if (can_install.find(pkg) != can_install.end())
                cout << "[Install Existing] " << pkg << ": " << adb::install_existing(pkg);
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
            cout << "[Uninstall] " << pkg << ": " << adb::uninstall(pkg);
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