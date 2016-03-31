#ifndef _DLLHANDLER_
#define _DLLHANDLER_

#include "..\Dictionary\includes\CommandHandler.h"
#include "..\Dictionary\includes\I_Dictionary.h"
#include <vector>
#include <string> 
using namespace std;

class TranslateHandler : public CommandHandler 
{
public:
    TranslateHandler(I_Dictionary& instance);
    vector<_Flags> GetFlag();
    void           Execute(const vector<string>& args, const vector<_Flags>& flag, string& result);
    string         Help();

private:
    I_Dictionary*  dll;
    vector<_Flags> flags;
};

#endif // _DLLHANDLER_