#include "args.hpp"

Arguments parse_arguments(int argc, char *argv[])
{
    Arguments args;
    for (int i = 1; i < argc; i++)
    {
        if (!args.parsing_status.empty())
            return args;
        string arg = argv[i];
        if (arg == "-i" || arg == "--install")
        {
            if (args.option == Arguments::Option::Null)
                args.option = Arguments::Option::Install;
            else
                args.parsing_status = "Found Multiple Options Expected Only One";
        }
        else if (arg == "-u" || arg == "--uninstall")
        {
            if (args.option == Arguments::Option::Null)
                args.option = Arguments::Option::Uninstall;
            else
                args.parsing_status = "Found Multiple Options Expected Only One";
        }
        else if (arg == "-h" || arg == "--help")
        {
            if (args.option == Arguments::Option::Null)
                args.option = Arguments::Option::Help;
            else
                args.parsing_status = "Found Multiple Options Expected Only One";
        }
        else if (arg == "-v" || arg == "--version")
        {
            if (args.option == Arguments::Option::Null)
                args.option = Arguments::Option::Version;
            else
                args.parsing_status = "Found Multiple Options Expected Only One";
        }
        else if (arg == "-l" || arg == "--list")
        {
            if (args.specifier == Arguments::Specifier::Null)
            {
                args.specifier = Arguments::Specifier::List;
                if (i + 1 < argc)
                    args.specified_packages = argv[++i];
                else
                    args.parsing_status = "Expected string of packages separated with ,";
            }
            else
                args.parsing_status = "Found Multiple Specifiers Expected Only One";
        }
        else if (arg == "-f" || arg == "--file")
        {
            if (args.specifier == Arguments::Specifier::Null)
            {
                args.specifier = Arguments::Specifier::File;
                if (i + 1 < argc)
                    args.specified_packages = argv[++i];
                else
                    args.parsing_status = R"(Expected file path containg packages separated with \n)";
            }
            else
                args.parsing_status = "Found Multiple Specifiers Expected Only One";
        }
        else if (arg == "-s" || arg == "--serial")
        {
            if (!args.is_serial_specified)
            {
                args.is_serial_specified = true;
                if (i + 1 < argc)
                    args.serial = argv[++i];
                else
                    args.parsing_status = "Expected string device serial";
            }
            else
                args.parsing_status = "Found Multiple Serials Expected Only One";
        }
        else
            args.parsing_status = "Invalid Option or Specifier: " + arg;
    }
    return args;
}
