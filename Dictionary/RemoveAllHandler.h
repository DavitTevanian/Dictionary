#ifndef _REMOVEALLHANDLER_
#define _REMOVEALLHANDLER_

#include "includes\CommandHandler.h"
#include "includes\I_Dictionary.h"
#include "includes\I_IOManager.h"
#include "includes\\QueryInterface.h"

class RemoveAllHandler : public CommandHandler 
{
public:
    RemoveAllHandler(I_Dictionary& instance, QueryInterface& check);
    vector<_Flags> GetFlag();
    void           Execute(const vector<string>& args, const vector<_Flags>& flag, string& result);
    string         Help();

private:
    I_Dictionary*   removeAll;
    QueryInterface* _ioManager;
    vector<_Flags>  flags;
};

#endif //_REMOVEALLHANDLER_