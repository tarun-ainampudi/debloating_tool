#include <iostream>
#include "debloat.hpp"
using namespace std;

int main()
{
    string packages = debloat::get_packages();
    cout << packages << endl;
    return 0;
}