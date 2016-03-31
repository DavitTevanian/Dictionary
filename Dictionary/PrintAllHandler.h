#ifndef _PRINTALLHANDLER_
#define _PRINTALLHANDLER_

#include "includes\CommandHandler.h"
#include "includes\I_Dictionary.h"

class PrintAllHandler : public CommandHandler
{
public:
    PrintAllHandler(I_Dictionary& instance);
    vector<_Flags> GetFlag();
    void           Execute(const vector<string>& args, const vector<_Flags>& flag, string& result);
    string         Help();

private:
    I_Dictionary*  printAll;
    vector<_Flags> flags;
};

#endif //_PRINTALLHANDLER_