#ifndef _LOGFILEHANDLER_
#define _LOGFILEHANDLER_

#include "includes\CommandHandler.h"
#include "includes\I_IOManager.h"

class LogFileHandler :public CommandHandler
{
public:
    LogFileHandler(I_IOManager& instance);
    vector<_Flags> GetFlag();
    void           Execute(const vector<string>& args, const vector<_Flags>& flag, string& result);
    string         Help();

private:
    I_IOManager*   _ioManagerLog;
    vector<_Flags> flags;
};

#endif // _LOGFILEHANDLER_