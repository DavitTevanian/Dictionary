#include "LoadDllHandler.h"
#include <algorithm>
#include <iostream>

LoadDllHandler::LoadDllHandler(I_CommandEngine & engine, I_Dictionary * instance, I_IOManager* ioMan, QueryInterface* userInt) :_comEng(engine),
_dict(instance), _ioMan(ioMan), _userInt(userInt) {
    _Flags flag;
    flag.flagName = "-unload";
    flag.exist = true;
    flag.argCount = 0;
    _flags.push_back(flag);

}

vector<CommandHandler::_Flags> LoadDllHandler::GetFlag() {
    return _flags;
}

string LoadDllHandler::Help() {
    return "LOAD DLL     Lets to load new commands from DLL. Also you can use this\n"
        "             flag -unload ,for unload already loaded DLL\n";
}

I_IOManager* LoadDllHandler::getIOManager() const 
{
    return _ioMan;
}

QueryInterface* LoadDllHandler::getQueryInterface() const 
{
    return _userInt;
}

I_CommandEngine* LoadDllHandler::getComandEngine() const 
{
    return &_comEng;
}

I_Dictionary* LoadDllHandler::getDictionary() const 
{
    return _dict;
}

string LoadDllHandler::LoadDll(const string& path) 
{
    for (size_t i = 0; i < _loadedDLLs.size(); ++i)
        if (_loadedDLLs[i].path == path)
            return "DLL is already loaded";

    HMODULE hDLL = LoadLibraryA(path.c_str());
    if (!hDLL)
        return "DLL not found";

    FP_GetDLLInterface dllFunction = (FP_GetDLLInterface)GetProcAddress(hDLL, "getDLLInterface");
    if (!dllFunction)
        return "Not correct DLL";

    DLLInterface* dllInterface = dllFunction();
    if (!dllInterface)
        return "Not correct DLL";

    DLLInterface::HandlersMap dllHandlers = dllInterface->createHandlers(*this);

    LoadedDLL loadedDLL;
    loadedDLL.hDLL = hDLL;
    loadedDLL.dllInterface = dllInterface;
    loadedDLL.path = path;
    for (map<string, CommandHandler&>::iterator i = dllHandlers.begin(); i != dllHandlers.end(); ++i) {
        _comEng.Register(i->first, i->second);
        loadedDLL.loadedCommands.push_back(i->first);
    }

    if (loadedDLL.loadedCommands.empty())
    {
        dllInterface->releaseHandlers();
        FreeLibrary(hDLL);
        return "No commands have been added";
    }

    _loadedDLLs.push_back(loadedDLL);

    size_t commandsAdded = loadedDLL.loadedCommands.size();
    return to_string(commandsAdded) + "Dll commands have been loaded !";
}

string LoadDllHandler::UnLoadDll(const string& path) 
{
    for (size_t i = 0; i < _loadedDLLs.size(); ++i)
        if (_loadedDLLs[i].path == path) {

            for (size_t j = 0; j < _loadedDLLs[i].loadedCommands.size(); ++j)
                _comEng.UnRegister(_loadedDLLs[i].loadedCommands[i]);

            _loadedDLLs[i].dllInterface->releaseHandlers();
            if (FreeLibrary(_loadedDLLs[i].hDLL))
                return "DLL successfuly unloaded";
            else
                return "DLL unload failed";
        }

    return "Specified DLL is not loaded";

}

void LoadDllHandler::Execute(const vector<string>& args, const vector<_Flags>& flag, string& result) 
{
    if (args.size() > 2 && args[2].substr(args[2].size() - 4, 4) != ".dll")
        result = "Specified file must have \".dll\" extension";

    else if (args.size() == 3) {
        result = LoadDll(args[2]);
    }
    else if (args.size() == 4) {
        for (size_t i = 0; i < flag.size(); ++i)
            if (flag[i].flagName == args[3]) {
                result = UnLoadDll(args[2]);
                break;
            }
    }
    else
        result = "Please enter correct arguments ";
}