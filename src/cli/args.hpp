#include <string>

using namespace std;

struct Arguments
{
    enum class Option
    {
        Install,
        Uninstall,
        Version,
        Help,
        Null,
    };

    enum class Specifier
    {
        List,
        File,
        Null,
    };
    
    Option option = Option::Null;
    Specifier specifier = Specifier::Null;
    string specified_packages;
    bool is_serial_specified = false;
    string serial;
    string parsing_status;
};

Arguments parse_arguments(int argc, char *argv[]);
