#ifndef _TRANSLATEHANDLER_
#define _TRANSLATEHANDLER_

#include "includes\CommandHandler.h"
#include "includes\I_Dictionary.h"

class TranslateHandler :public CommandHandler 
{
public:
    TranslateHandler(I_Dictionary& instance);
    vector<_Flags> GetFlag();
    void           Execute(const vector<string>& args, const vector<_Flags>& flag, string& result);
    string         Help();

private:
    I_Dictionary*  translate;
    vector<_Flags> flags;
};

#endif //_TRANSLATEHANDLER_