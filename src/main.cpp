#include <iostream>

#include "debloat/debloat.hpp"
#include "adb/adb.hpp"
#include "adb/device.hpp"
#include "cmd/exec.hpp"
#include "cli/args.hpp"

using namespace std;

#define DEBLOAT_VERSION "0.1.0"

void display_help()
{
    cout << "Debloating Tool v" << DEBLOAT_VERSION <<
        R"(
Usage:
    debloat -u -l <pkg1,pkg2,...>
    debloat -u -f <packages.txt>
    debloat -i <app.apk>

Options:
    -u, --uninstall    Uninstall packages
    -i, --install      Install APK or Existing packages
    -v, --version      Show Version
    -h, --help         Show Usage

Specifiers:
    -l, --list         Comma-separated package list
    -f, --file         Text file containing one package per line

Examples:
    debloat -u -l com.xyz.abc,in.def.uvw
    debloat -u -f packages.txt
    debloat -i app.apk)"
         << endl;
}

string convert_file_to_list(const char *path)
{
    string file_content = get_file_content(path);
    for (size_t i = 0; i < file_content.size(); i++)
    {
        if (file_content[i] == '\n')
            file_content[i] = ',';
    }
    return file_content;
}

int main(int argc, char *argv[])
{
    Arguments args = parse_arguments(argc, argv);

    if (!args.parsing_status.empty())
    {
        cout << "[Error] Parsing Failed: " << args.parsing_status << endl;
        display_help();
        return 0;
    }

    switch (args.option)
    {
    case Arguments::Option::Null:
        cout << "Invalid Option (or) Option not specified" << endl;
        display_help();
        return 0;

    case Arguments::Option::Help:
        display_help();
        return 0;

    case Arguments::Option::Version:
        cout << DEBLOAT_VERSION << endl;
        return 0;

    case Arguments::Option::Install:
        if (args.specifier == Arguments::Specifier::List)
            debloat::install_existing_pkgs(args.specified_packages.c_str());
        else if (args.specifier == Arguments::Specifier::File)
        {
            string pkgs = convert_file_to_list(args.specified_packages.c_str());
            debloat::install_existing_pkgs(pkgs.c_str());
        }
        else
            cout << "[Error] Expected Specifier: --list (or) --file";
        return 0;

    case Arguments::Option::Uninstall:
        if (args.specifier == Arguments::Specifier::List)
            debloat::uninstall_packages(args.specified_packages.c_str());
        else if (args.specifier == Arguments::Specifier::File)
        {
            string pkgs = convert_file_to_list(args.specified_packages.c_str());
            debloat::uninstall_packages(pkgs.c_str());
        }
        else
            cout << "[Error] Expected Specifier: --list (or) --file";
        return 0;
    }
}