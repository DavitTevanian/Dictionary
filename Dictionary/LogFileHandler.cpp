#include "LogFileHandler.h"

#include <iostream>
#include <iomanip>

LogFileHandler::LogFileHandler(I_IOManager& instance) : _ioManagerLog(&instance) 
{
    _Flags flag;
    flag.flagName = "-unlog";
    flag.exist = true;
    flag.argCount = 0;
    flags.push_back(flag);
    flag.flagName = "-print";
    flag.exist = true;
    flag.argCount = 0;
    flags.push_back(flag);
}

void LogFileHandler::Execute(const vector<string>& args, const vector<_Flags>& flag, string& result) 
{
    string file, answer, query = "Are you sure want to close log file? [yes / no]  ";

    if (args.size() == 2) {
        if (_ioManagerLog->StartLog(args[1]))
            result = "File " + args[1] + " is open !\n";
        else
            result = "File " + args[1] + " doesn't open !\n";
    }
    else if (args.size() == 3) {
        for (size_t i = 0; i < flag.size(); ++i) {
            if (flag[i].flagName == args[2]) {
                if (flag[i].flagName == "-print") {
                    _ioManagerLog->Print(args[1]);
                }
                else if (flag[i].flagName == "-unlog") {
                    if (_ioManagerLog->EndLog()) {
                        result = "\nFile " + args[1] + " closed !\n";
                        break;
                    }
                    else {
                        result = "\nFile " + args[1] + " didn't close !\n";
                        break;
                    }
                }
            }
        }
    }
    else
        result = "Please enter correct arguments...\n ";

}

string LogFileHandler::Help() 
{
    return "LOG          If you want that your actions to preserve in the file.\n"
        "             For that you should input LOG FILENAME\n"
        "             also you can use this flags -unlog and -print\n";
}

vector<CommandHandler::_Flags> LogFileHandler::GetFlag() 
{
    return flags;
}