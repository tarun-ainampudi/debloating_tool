#pragma once

#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

namespace util
{
    vector<string> split_string(const string &input, char delimiter);

    string trim_string(const string &input);

    unordered_set<string>
    uset_difference(const unordered_set<string> &a,
                    const unordered_set<string> &b);

    unordered_set<string>
    uset_intersection(const unordered_set<string> &a,
                      const unordered_set<string> &b);
}