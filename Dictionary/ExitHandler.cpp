#include "ExitHandler.h"

#include <iostream>

ExitHandler::ExitHandler(CommandEngine& instance, IOManager& ioManager) : _engineExit(&instance), _ioManager(&ioManager)
{
    _Flags flag;
    flags.push_back(flag);
}

void ExitHandler::Execute(const vector<string>& args, const vector<_Flags>& flag, string& result) 
{
    string answer, query = "Are you sure want to exit the programm ? [yes / no]  ";
    if (args.size() == 1) {
        if (_ioManager->QueryUser(query, answer)) {
            if (answer == "yes")
                _engineExit->_run = false;
            else if (answer == "no")
                result = "";
            else
                result = "\nEnter correct answer !";
        }
        else
            _engineExit->_run = false;
    }
    else
        result = "This command doesn't have arguments... ";
}

string ExitHandler::Help()
{
    return "EXIT         Finishes the work of programm. For that you should input EXIT. \n";
}

vector<CommandHandler::_Flags> ExitHandler::GetFlag() 
{
    return flags;
}