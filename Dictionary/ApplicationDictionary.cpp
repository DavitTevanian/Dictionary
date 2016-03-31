#include "ApplicationDictionary.h"
#include "Dictionary.h"
#include "AddHandler.h"
#include "CountHandler.h"
#include "PrintAllHandler.h"
#include "RemoveAllHandler.h"
#include "DeleteHandler.h"
#include "TranslateHandler.h"
#include "HelpHandler.h"
#include "ExitHandler.h"
#include "LogFileHandler.h"
#include "SilentModeHandler.h"
#include "IOManager.h"
#include "QueryInterface.h"
#include "CommandEngine.h"
#include "LoadDllHandler.h"

void ApplicationDictionary::Run(int argCount, vector<string>& arguments) 
{
    CommandEngine engine;
    Dictionary  dictionary;
    IOManager iomanager;
    dictionary.Start();

    AddHandler add(dictionary);
    CountHandler count(dictionary);
    PrintAllHandler printAll(dictionary);
    RemoveAllHandler removeAll(dictionary, iomanager);
    DeleteHandler remove(dictionary, iomanager);
    TranslateHandler translate(dictionary);
    HelpHandler help(engine);
    ExitHandler exit(engine, iomanager);
    LogFileHandler logFile(iomanager);
    SilentModeHandler silentMode(iomanager);
    LoadDllHandler loadDLL(engine, &dictionary);

    engine.Register("help", help);
    engine.Register("print all", printAll);
    engine.Register("remove all", removeAll);
    engine.Register("add", add);
    engine.Register("count", count);
    engine.Register("translate", translate);
    engine.Register("delete", remove);
    engine.Register("exit", exit);
    engine.Register("log", logFile);
    engine.Register("silent", silentMode);
    engine.Register("load dll", loadDLL);

    string beginString;
    if (argCount > 1) {
        for (int i = 1; i < argCount; ++i)
            beginString = beginString + arguments[i] + " ";
        beginString = beginString.substr(0, beginString.length() - 1);
        engine.Run(beginString, true);
    }
    else
        engine.Run(beginString, false);
}

