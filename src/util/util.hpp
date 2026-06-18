#pragma once

#include <string>
#include <vector>

using namespace std;

namespace util
{
    vector<string> split_string(const string &input, char delimiter);

    string trim_string(const string &input);
}