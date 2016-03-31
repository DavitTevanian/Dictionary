#ifndef _COUNTHANDLER_
#define _COUNTHANDLER_

#include "includes\CommandHandler.h"
#include "includes\I_Dictionary.h"

class CountHandler :public CommandHandler
{
public:
    CountHandler(I_Dictionary& instance);
    vector<_Flags> GetFlag();
    void           Execute(const vector<string>& args, const vector<_Flags>& flag, string& result);
    string         Help();

private:
    I_Dictionary*  count;
    vector<_Flags> flags;
};

#endif //_COUNTHANDLER_