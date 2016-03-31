#include "HelpHandler.h"

#include <iostream>
#include <iomanip>

HelpHandler::HelpHandler(CommandEngine& instance) : help(&instance) 
{
    _Flags flag;
    flags.push_back(flag);
}

void HelpHandler::Execute(const vector<string>& args, const vector<_Flags>& flag, string& result) 
{
    bool choose = false;
    if (args.size() == 1)
        result = Help();
    else if (args.size() == 2) {
        for (vector<CommandSpace>::iterator it = help->_registerCommands->begin(); it != help->_registerCommands->end(); ++it) {
            if (args[1] == it->command) {
                result = it->handler->Help();
                choose = true;
            }
        }
        if (choose == false)
            result = "This command doesn't contain such argument !\nPlease input correct arguments \n";
    }
    else if (args.size() == 3) {
        for (vector<CommandSpace>::iterator it = help->_registerCommands->begin(); it != help->_registerCommands->end(); ++it) {
            if ((args[1] + " " + args[2]) == it->command) {
                result = it->handler->Help();
                choose = true;
            }
        }
        if (choose == false)
            result = "This command doesn't contain such argument !\nPlease input correct arguments \n";
    }
    else
        result = "Dictionary doesn't contain such command !\n Please input correct command \n";
}

string HelpHandler::Help() 
{
    string _help;
    for (vector<CommandSpace>::iterator it = help->_registerCommands->begin() + 1; it != help->_registerCommands->end(); ++it)
        _help += it->handler->Help();

    return _help;
}

vector<CommandHandler::_Flags> HelpHandler::GetFlag() 
{
    return flags;
}