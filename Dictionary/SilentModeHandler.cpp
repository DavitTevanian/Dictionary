#include "SilentModeHandler.h"
#include <iostream>

SilentModeHandler::SilentModeHandler(I_IOManager& instance) : ioManagerSilent(&instance) 
{
    _Flags flag;
    flag.flagName = "-on";
    flag.exist = true;
    flag.argCount = 0;
    flags.push_back(flag);
    flag.flagName = "-off";
    flag.exist = true;
    flag.argCount = 0;
    flags.push_back(flag);
}


void SilentModeHandler::Execute(const vector<string>& args, const vector<_Flags>& flag, string& result) 
{
    if (args.size() == 2) {
        for (size_t i = 0; i < flag.size(); ++i)
            if (flag[i].flagName == args[1]) {
                if (flag[i].flagName == "-on")
                    ioManagerSilent->StartSilent();
                else if (flag[i].flagName == "-off")
                    ioManagerSilent->StopSilent();
                break;
            }
    }
    else
        result = "This command can recives only one flag as argument ! ";
}

string SilentModeHandler::Help() 
{
    return "SILENT       Turn on or off the feature request through flags. For that you\n             should input SILENT -ON or SILENT -OFF. \n";
}

vector<CommandHandler::_Flags> SilentModeHandler::GetFlag() 
{
    return flags;
}

