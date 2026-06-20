#include <iostream>

#include "debloat/debloat.hpp"
#include "adb/adb.hpp"
#include "cmd/exec.hpp"

using namespace std;

enum class Option
{
    Install,
    Uninstall,
    Help,
};

enum class Specifier
{
    List,
    File,
    Null,
};

void display_help()
{
    cout << R"(Usage:
    debloat -u -l <pkg1,pkg2,...>
    debloat -u -f <packages.txt>
    debloat -i <app.apk>

Options:
    -u, --uninstall    Uninstall packages
    -i, --install      Install APK or Existing packages
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

Option parseOptionArg(char *argv[])
{
    string arg = argv[1];
    if (arg == "-i" || arg == "--install")
        return Option::Install;
    if (arg == "-u" || arg == "--uninstall")
        return Option::Uninstall;
    return Option::Help;
}

Specifier parseSpecifierArg(char *argv[])
{
    string arg = argv[2];
    if (arg == "-l" || arg == "--list")
        return Specifier::List;
    if (arg == "-f" || arg == "--file")
        return Specifier::File;
    return Specifier::Null;
}

int main(int argc, char *argv[])
{
    if (argc == 4)
    {
        Option option = parseOptionArg(argv);
        Specifier specifier = parseSpecifierArg(argv);
        if (option == Option::Help || specifier == Specifier::Null)
        {
            cout << "Invalid Option or Specifier" << endl;
            display_help();
            return 0;
        }
        else
        {
            string specified_pkgs;
            if (specifier == Specifier::File)
            {
                string file_content = get_file_content(argv[3]);
                for (size_t i = 0; i < file_content.size(); i++)
                {
                    if (file_content[i] == '\n')
                        file_content[i] = ',';
                }
                specified_pkgs = file_content;
            }
            else
            {
                specified_pkgs = argv[3];
            }
            if (option == Option::Install)
            {
                debloat::install_existing_pkgs(specified_pkgs.c_str());
            }
            else
            {
                debloat::uninstall_packages(specified_pkgs.c_str());
            }
        }
    }
    return 0;
}