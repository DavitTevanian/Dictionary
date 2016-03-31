#include "DeleteHandler.h"

#include <iostream>

DeleteHandler::DeleteHandler(I_Dictionary& instance, QueryInterface& check) : remove(&instance), _ioManager(&check) 
{
    _Flags flag;
    flag.flagName = "-remove";
    flag.exist = true;
    flag.argCount = 1;
    flags.push_back(flag);
}

void DeleteHandler::Execute(const vector<string>& args, const vector<_Flags>& flag, string& result) 
{
    string answer, query = "Are you sure want to delete ? [yes / no]  ";

    if (args.size() == 2 && args[1].at(0) != '-') {
        if (_ioManager->QueryUser(query, answer)) {
            if (answer == "yes")
                result = remove->Delete(args[1]);
            else if (answer == "no")
                result = "";
            else
                result = "\nEnter correct answer !";

        }
        else
            result = remove->Delete(args[1]);
    }
    else if (args.size() == 4) {
        for (size_t i = 0; i < flag.size(); ++i) {
            if (flag[i].flagName == args[2]) {
                if (flag[i].flagName == "-remove") {
                    if (_ioManager->QueryUser(query, answer)) {
                        if (answer == "yes") {
                            result = remove->DeleteByFlag(args[1], args[3]);
                            break;
                        }
                        else if (answer == "no") {
                            result = "";
                            break;
                        }
                        else {
                            result = "\nEnter correct answer !";
                            break;
                        }
                    }
                    else {
                        result = remove->DeleteByFlag(args[1], args[3]);
                        break;
                    }
                }
            }
        }
    }
    else
        result = "Please enter correct arguments... ";
}

string DeleteHandler::Help() 
{
    return "DELETE       Deletes word in dictionary,if that existing in dictionary.\n"
        "             For that you should input DELETE WORD\n             Also you can use this flag  -remove\n"
        "             for delete chosen meaning. For that you should input DELETE\n             WORD -remove MEANING \n";
}

vector<CommandHandler::_Flags> DeleteHandler::GetFlag() 
{
    return flags;
}