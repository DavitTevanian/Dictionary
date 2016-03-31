#ifndef _EXITHANDLER_
#define _EXITHANDLER_

#include "includes\CommandHandler.h"
#include "CommandEngine.h"
#include "IOManager.h"

class ExitHandler :public CommandHandler 
{
public:
    ExitHandler(CommandEngine& instance, IOManager& ioManager);
    vector<_Flags> GetFlag();
    void           Execute(const vector<string>& args, const vector<_Flags>& flag, string& result);
    string         Help();

private:
    CommandEngine* _engineExit;
    IOManager*     _ioManager;
    vector<_Flags> flags;
};

#endif // _EXITHANDLER_