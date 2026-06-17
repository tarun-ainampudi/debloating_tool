#include <iostream>
#include <stdexcept>
#include <cstdio>
#include <string>

std::string exec(const char *cmd)
{
    char buffer[128];
    std::string output = "";
    FILE *pipe = _popen(cmd, "r");
    if (!pipe)
    {
        std::cout << "[Error] Unable to read cmd output" << std::endl;
        return NULL;
    }
    try
    {
        while (fgets(buffer, sizeof buffer, pipe) != NULL)
        {
            output += buffer;
        }
    }
    catch (const char *err)
    {
        std::cout << "[Error] " << err << std::endl;
        return NULL;
    }
    _pclose(pipe);
    return output;
}