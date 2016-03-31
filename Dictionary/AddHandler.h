#ifndef _ADDHANDLER_
#define _ADDHANDLER_

#include "includes\CommandHandler.h"
#include "includes\I_Dictionary.h"

class AddHandler : public CommandHandler 
{
public:
    AddHandler(I_Dictionary& instance);
    vector<_Flags> GetFlag();
    void           Execute(const vector<string>& args, const vector<_Flags>& flag, string& result);
    string         Help();

private:
    I_Dictionary*  add;
    vector<_Flags> flags;
};

#endif // _ADDHANDLER_