#pragma once

#include <string>
#include <unordered_set>

using namespace std;

namespace debloat
{    
    void uninstall_packages(const char* pkgs);

    void install_existing_pkgs(const char *pkgs);
}