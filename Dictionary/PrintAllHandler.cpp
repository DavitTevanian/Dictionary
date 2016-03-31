#include "PrintAllHandler.h"

#include <iostream>

PrintAllHandler::PrintAllHandler(I_Dictionary& instance) : printAll(&instance) 
{
    _Flags flag;
    flags.push_back(flag);
}

void PrintAllHandler::Execute(const vector<string>& args, const vector<_Flags>& flag, string& result) 
{
    if (args.size() == 2) {
        printAll->ProcessIndicator(printAll->Count());
        result = printAll->PrintAll();
    }
    else
        result = "This command doesn't have arguments ";

}

string PrintAllHandler::Help() 
{
    return "PRINT ALL    Prints all words in dictionary. For that you should input\n             PRINT ALL. \n";
}

vector<CommandHandler::_Flags> PrintAllHandler::GetFlag() 
{
    return flags;
}