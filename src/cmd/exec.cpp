#include "exec.hpp"

#include <iostream>
#include <stdexcept>
#include <cstdio>

std::string exec(const char *cmd)
{
    char buffer[128];
    std::string output = "";

#ifdef _WIN32
    FILE *pipe = _popen(cmd, "r");
#else
    FILE *pipe = popen(cmd, "r");
#endif

    if (!pipe)
    {
        std::cout << "[Error] Unable to read cmd output" << std::endl;
        return "";
    }
    try
    {
        while (fgets(buffer, sizeof buffer, pipe) != NULL)
        {
            output += buffer;
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "[Error] " << e.what() << std::endl;
        return "";
    }

#ifdef _WIN32
    _pclose(pipe);
#else
    pclose(pipe);
#endif

    return output;
}

std::string get_file_content(const char *path)
{
#ifdef _WIN32
    return exec((std::string("type \"") + path + "\"").c_str());
#else
    return exec((std::string("cat \"") + path + "\"").c_str());
#endif
}