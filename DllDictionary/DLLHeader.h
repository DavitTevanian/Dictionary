#ifndef _DLLHANDLER_
#define _DLLHANDLER_

#include "CommandHandler.h"
#include "Dictionary.h"
#include "IOManager.h"
#include "QueryInterface.h"
#include <vector>
#include <string> 
using namespace std;

class DLLHandler:public CommandHandler{

public:
	DLLHandler(Dictionary & instance);
    vector<_Flags> GetFlag();
	void Execute(const vector<string> & args,const vector<_Flags> & flag,string & result);
	string Help();

private:
	Dictionary * dll;
	vector<_Flags> flags;
};

#endif // _DLLHANDLER_