#ifndef _SILENTMODEHANDLER_
#define _SILENTMODEHANDLER_

#include "includes\CommandHandler.h"
#include "includes\I_IOManager.h"

class SilentModeHandler : public CommandHandler
{
public:
    SilentModeHandler(I_IOManager& instance);
    vector<_Flags> GetFlag();
    void           Execute(const vector<string>& args, const vector<_Flags>& flag, string& result);
    string         Help();

private:
    I_IOManager*   ioManagerSilent;
    vector<_Flags> flags;
};

#endif //_SILENTMODEHANDLER_