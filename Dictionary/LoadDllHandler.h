#ifndef _LOADDLLHANDLER_
#define _LOADDLLHANDLER_

#include "includes\CommandHandler.h"
#include "includes\I_Dictionary.h"
#include "includes\CommandStructure.h"
#include "includes\I_CommandEngine.h"
#include "includes\DllReference.h"
#include "includes\QueryInterface.h"
#include <windows.h>

class LoadDllHandler : public CommandHandler, public Provider 
{
    struct LoadedDLL
    {
        HMODULE        hDLL;
        DLLInterface*  dllInterface;
        string         path;
        vector<string> loadedCommands;
    };

public:
    LoadDllHandler(I_CommandEngine& engine, I_Dictionary* instance, I_IOManager* ioMan = 0, QueryInterface* userInt = 0);
    virtual ~LoadDllHandler() {};
    vector<_Flags> GetFlag();
    void           Execute(const vector<string>& args, const vector<_Flags>& flag, string& result);
    string         Help();

private:
    string LoadDll(const string& path);
    string UnLoadDll(const string& path);
    I_IOManager*     getIOManager() const;
    QueryInterface*  getQueryInterface() const;
    I_CommandEngine* getComandEngine() const;
    I_Dictionary*    getDictionary() const;

private:
    I_Dictionary*     _dict;
    I_IOManager*      _ioMan;
    I_CommandEngine&  _comEng;
    QueryInterface*   _userInt;
    vector<LoadedDLL> _loadedDLLs;
    vector<_Flags>    _flags;
};

#endif //_LOADDLLHANDLER_