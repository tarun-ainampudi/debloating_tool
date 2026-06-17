#include <iostream>
#include "debloat.hpp"
#include "cmd/exec.hpp"

using namespace std;

int main()
{
    string n = debloat::get_packages();
    cout << n << endl;
    string packages = exec("adb shell pm list packages");
    cout << packages << endl;
    return 0;
}