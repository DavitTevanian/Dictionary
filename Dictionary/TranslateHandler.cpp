#include "TranslateHandler.h"

#include <iostream>

TranslateHandler::TranslateHandler(I_Dictionary& instance) : translate(&instance) 
{
    _Flags flag;
    flags.push_back(flag);
}

void TranslateHandler::Execute(const vector<string>& args, const vector<_Flags>& flag, string& result) 
{
    if (args.size() == 2)
        result = translate->Translate(args[1]);
    else
        result = "Please enter correct arguments... ";
}

string TranslateHandler::Help() 
{
    return "TRANSLATE    Translates the word that entered,if that word existing\n"
        "             in dictionary. For that you should input TRANSLATE WORD. \n";
}

vector<CommandHandler::_Flags> TranslateHandler::GetFlag() 
{
    return flags;
}