#ifndef _HELPHANDLER_
#define _HELPHANDLER_

#include "includes\CommandHandler.h"
#include "CommandEngine.h"

class HelpHandler :public CommandHandler 
{
public:
    HelpHandler(CommandEngine& instance);
    vector<_Flags> GetFlag();
    void           Execute(const vector<string>& args, const vector<_Flags>& flag, string& result);
    string         Help();

private:
    CommandEngine* help;
    vector<_Flags> flags;
};

#endif // _HELPHANDLER_