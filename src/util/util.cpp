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
        return result;
    }
}