#include "exec.hpp"

#include <iostream>
#include <stdexcept>
#include <cstdio>

std::string exec(const char *cmd)
{
    char buffer[128];
    std::string output = "";
    FILE *pipe = _popen(cmd, "r");
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
    _pclose(pipe);
    return output;
}