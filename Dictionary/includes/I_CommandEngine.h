#ifndef _I_COMMANDENGINE_
#define _I_COMMANDENGINE_

#include "CommandStructure.h"

class I_CommandEngine{

public:

	virtual void Run(string & inputString,bool cmd)=0;
	virtual void Register(const string & commandName, CommandHandler & handler)=0;
        virtual void UnRegister(const string & commandName)=0;

private:
	virtual bool FindFlags(const vector<string> & vectInputString, CommandHandler * handler)=0;
	virtual pair<bool,CommandHandler *> FindCommand(const vector<string> & vectInputString, const vector<CommandSpace> * commands)=0;
	virtual bool Suggestion(string & wrongWord,string & correctWord)=0;
	virtual void Complete( string & substring)=0;
	virtual void StartOfTAB(string & suggestionLine)=0;
	virtual string _getLine()=0;
protected:
	virtual ~I_CommandEngine() {};
	
};

#endif // _I_COMMANDENGINE_