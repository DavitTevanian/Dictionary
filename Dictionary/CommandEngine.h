#ifndef _COMMANDENGINE_
#define _COMMANDENGINE_
#include "includes\I_CommandEngine.h"
#include "includes\CommandStructure.h"
#include "AutoComplete.h"
#include "IOManager.h"

class CommandEngine : public I_CommandEngine 
{
public:
    friend class ExitHandler;
    friend class HelpHandler;

    CommandEngine();
    ~CommandEngine();
    void Run(string& inputString, bool cmd);
    void Register(const string& commandName, CommandHandler& handler);
    void UnRegister(const string& commandName);

private:
    pair<bool, CommandHandler*> FindCommand(const vector<string>& vectInputString, const vector<CommandSpace>* commands);
    bool                        FindFlags(const vector<string>& vectInputString, CommandHandler* handler);
    bool                        Suggestion(string& wrongWord, string& correctWord);
    void                        Complete(string& substring);
    void                        StartOfTAB(string& suggestionLine);
    string                      _getLine();
    vector<CommandSpace>* _registerCommands;
    AutoComplete          autoComplete;
    IOManager             _ioManager;
    bool                  _run;
    bool                  _continue;
};

#endif // _COMMANDENGINE_