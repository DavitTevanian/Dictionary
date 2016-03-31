#include "AddHandler.h"

#include <iostream>

AddHandler::AddHandler(I_Dictionary& instance) : add(&instance) 
{
    _Flags flag;
    flag.flagName = "-append";
    flag.exist = true;
    flag.argCount = 1;
    flags.push_back(flag);
    flag.flagName = "-replace";
    flag.exist = true;
    flag.argCount = 1;
    flags.push_back(flag);
}


void AddHandler::Execute(const vector<string>& args, const vector<_Flags>& flag, string& result) 
{
    if (args.size() == 3 && args[1].at(0) != '-' && args[2].at(0) != '-')
        result = add->AddWord(args[1], args[2]);
    else if (args.size() == 4) {
        for (size_t i = 0; i < flag.size(); ++i) {
            if (flag[i].flagName == args[2]) {
                if (flag[i].flagName == "-append")
                    result = add->Append(args[1], args[3]);
                else if (flag[i].flagName == "-replace")
                    result = add->Replace(args[1], args[3]);
                break;
            }
        }
    }
    else
        result = "Please enter correct arguments ";
}

string AddHandler::Help() 
{
    return "ADD          Adds a word in dictionary. For that you should input ADD WORD\n"
        "             TRANSLATION.Also you can use this flags  -append and  -replace\n             for append and"
        "replace meaning. For that you should input\n             ADD WORD -append MEANING or ADD WORD -replace MEANING. \n";
}

vector<CommandHandler::_Flags> AddHandler::GetFlag()
{
    return flags;
}