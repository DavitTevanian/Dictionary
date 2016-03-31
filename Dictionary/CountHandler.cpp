#include "CountHandler.h"

#include <iostream>

CountHandler::CountHandler(I_Dictionary& instance) : count(&instance) 
{
    _Flags flag;
    flag.exist = false;
    flag.flagName == "";
    flags.push_back(flag);
}


void CountHandler::Execute(const vector<string>& args, const vector<_Flags>& flag, string& result) 
{
    if (args.size() == 1) {
        cout << endl << count->Count();
    }
    else
        result = "This command doesn't have arguments... ";
}

string CountHandler::Help()
{
    return "COUNT        Receives count of words in dictionary. For that you should\n             input COUNT. \n";
}

vector<CommandHandler::_Flags> CountHandler::GetFlag() 
{
    return flags;
}