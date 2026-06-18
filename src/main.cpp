#include <iostream>

#include "debloat/debloat.hpp"
#include "adb/adb.hpp"

using namespace std;

int main()
{
    string packages = debloat::get_packages();
    // cout << packages << endl;
    vector<adb::Device> devices = adb::get_adb_devices();
    for (size_t i = 0; i < devices.size(); i++)
    {
        cout << "Device [" << i << "]" << endl;
        cout << devices[i].serial << " : " << devices[i].state;
    }
    return 0;
}