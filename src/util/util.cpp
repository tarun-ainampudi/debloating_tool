#include "util.hpp"

namespace util
{
    vector<string> split_string(const string &input, char delimiter)
    {
        vector<string> result;
        string temp = "";
        for (auto it = input.cbegin(); it != input.cend(); it++)
        {
            if (*it == delimiter)
            {
                result.push_back(temp);
                temp = "";
            }
            else
            {
                temp += *it;
            }
        }
        result.push_back(temp);
        return result;
    }

    string trim_string(const string &input)
    {
        size_t start = input.find_first_not_of(" \t\n\r\f\v");

        if (start == string::npos)
            return "";

        size_t end = input.find_last_not_of(" \t\n\r\f\v");

        return input.substr(start, end - start + 1);
    }

    unordered_set<string>
    uset_difference(const unordered_set<string> &a,
                    const unordered_set<string> &b)
    {
        unordered_set<string> res;
        res.reserve(a.size());
        for (const auto &i : a)
        {
            if (b.find(i) == b.end())
            {
                res.insert(i);
            }
        }

        return res;
    }

    unordered_set<string>
    uset_intersection(const unordered_set<string> &a,
                      const unordered_set<string> &b)
    {
        unordered_set<string> res;
        if (a.size() < b.size())
        {
            res.reserve(a.size());
            for (const auto &i : a)
            {
                if (b.find(i) != b.end())
                {
                    res.insert(i);
                }
            }
        }
        else
        {
            res.reserve(b.size());
            for (const auto &i : b)
            {
                if (a.find(i) != a.end())
                {
                    res.insert(i);
                }
            }
        }
        return res;
    }
}