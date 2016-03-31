#include "RemoveAllHandler.h"

#include <iostream>

RemoveAllHandler::RemoveAllHandler(I_Dictionary& instance, QueryInterface& check) : removeAll(&instance), _ioManager(&check) 
{
    _Flags flag;
    flags.push_back(flag);
}

void RemoveAllHandler::Execute(const vector<string>& args, const vector<_Flags>& flag, string& result) 
{
    string answer, query = "Are you sure want to remove all ? [yes / no]  ";

    if (args.size() == 2) {
        if (_ioManager->QueryUser(query, answer)) {
            if (answer == "yes")
                result = removeAll->RemoveAll();
            else if (answer == "no")
                result = "";
            else
                result = "\nEnter correct answer !";

        }
        else
            result = removeAll->RemoveAll();
    }
    else
        result = "This command doesn't have arguments ";

}

string RemoveAllHandler::Help() 
{
    return "REMOVE ALL   Removes all words in dictionary. For that you should input\n             REMOVE ALL. \n";
}

vector<CommandHandler::_Flags> RemoveAllHandler::GetFlag() 
{
    return flags;
}