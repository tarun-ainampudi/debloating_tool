#pragma once

#include <unordered_set>
#include <string>

using namespace std;

namespace adb
{
    unordered_set<string> get_packages(const char *cmd);


    unordered_set<string> get_all_packages();


    unordered_set<string> get_enabled_packages();


    unordered_set<string> get_installed_packages();


    unordered_set<string> get_uninstalled_packages();
}