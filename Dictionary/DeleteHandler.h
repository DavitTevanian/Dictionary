#ifndef _DELETEHANDLER_
#define _DELETEHANDLER_

#include "includes\CommandHandler.h"
#include "includes\QueryInterface.h"
#include "includes\I_Dictionary.h"
#include "IOManager.h"

class DeleteHandler :public CommandHandler 
{
public:
    DeleteHandler(I_Dictionary& instance, QueryInterface& check);
    vector<_Flags> GetFlag();
    void           Execute(const vector<string>& args, const vector<_Flags>& flag, string& result);
    string         Help();

private:
    I_Dictionary*   remove;
    QueryInterface* _ioManager;
    vector<_Flags>  flags;
};

#endif //_DELETEHANDLER_