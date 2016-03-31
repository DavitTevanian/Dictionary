#include "CommandEngine.h"
#include <iostream>
#include <windows.h>
#include <algorithm>
CommandEngine::CommandEngine() :_run(true), _continue(false) 
{
    _registerCommands = new vector<CommandSpace>();
}
CommandEngine::~CommandEngine() 
{
    delete _registerCommands;
}

void CommandEngine::Register(const string& commandName, CommandHandler& handler) 
{
    CommandSpace data;
    data.command = commandName;
    data.handler = &handler;
    _registerCommands->push_back(data);
}
void CommandEngine::UnRegister(const string& commandName)
 {
    for (std::vector<CommandSpace>::iterator i = _registerCommands->begin();
    i != _registerCommands->end(); ++i)
        if (i->command == commandName)
        {
            _registerCommands->erase(i);
            return;
        }
}

bool CommandEngine::FindFlags(const vector<string>& vectInputString, CommandHandler* handler) 
{
    size_t foundPos, flagPos;
    string inputString;
    for (size_t i = 0; i < vectInputString.size(); ++i) {
        inputString += vectInputString[i] + " ";
        if (vectInputString[i][0] == '-')
            flagPos = i;
    }

    if (handler->GetFlag()[0].exist == false) {
        if ((foundPos = inputString.find_first_of("-")) != string::npos)
            return false;
        return true;
    }
    if ((foundPos = inputString.find_first_of("-")) != string::npos) {
        string flagname = inputString.substr(foundPos, inputString.find_first_of(" ", foundPos) - foundPos);
        for (size_t i = 0; i < handler->GetFlag().size(); ++i)
            if ((handler->GetFlag()[i].flagName == flagname) && (handler->GetFlag()[i].argCount == vectInputString.size() - flagPos - 1))
                return true;
        return false;
    }
    return true;
}

pair<bool, CommandHandler*> CommandEngine::FindCommand(const vector<string>& vectInputString, const vector<CommandSpace>* commands) 
{
    pair<bool, CommandHandler*> headerBool;
    for (vector<CommandSpace>::const_iterator it = commands->begin(); it != commands->end(); ++it) {
        if ((vectInputString.size() >= 2 && it->command == (vectInputString[0] + " " + vectInputString[1])) || (it->command == vectInputString[0])) {
            headerBool.second = it->handler;
            headerBool.first = true;
            return headerBool;
        }
    }
    headerBool.first = false;
    return headerBool;
}

bool CommandEngine::Suggestion(string& wrongWord, string& correctWord) 
{
    for (vector<CommandSpace>::iterator it = _registerCommands->begin(); it != _registerCommands->end(); ++it) {

        const size_t len1 = wrongWord.size(), len2 = it->command.size();
        vector<unsigned int> col(len2 + 1), prevCol(len2 + 1);

        for (unsigned int i = 0; i < prevCol.size(); i++)
            prevCol[i] = i;
        for (unsigned int i = 0; i < len1; i++) {
            col[0] = i + 1;
            for (unsigned int j = 0; j < len2; j++)
                col[j + 1] = min(min(prevCol[1 + j] + 1, col[j] + 1), prevCol[j] + (wrongWord[i] == it->command[j] ? 0 : 1));
            col.swap(prevCol);
        }
        if (prevCol[len2] < 3) {
            correctWord = it->command;
            return true;
        }
    }
    return false;
}

void CommandEngine::Complete(string& substring) 
{
    vector<string> autoCompleteVect;
    size_t xPos = substring.size();
    autoCompleteVect = autoComplete.Autocomplete(_registerCommands, substring);

    if (autoCompleteVect.size() == 1) {
        substring += autoCompleteVect[0];
        _ioManager.PrintInput(substring.substr(xPos), 1);
    }

    if (autoCompleteVect.size()>1) {
        string tempString = substring;
        substring += autoCompleteVect[0];
        for (size_t i = 1; i < autoCompleteVect.size(); ++i)
            substring += ", " + tempString + autoCompleteVect[i];
        _ioManager.PrintInput(substring.substr(xPos), 2);
        substring = "";
    }
}

void CommandEngine::StartOfTAB(string& suggestionLine) 
{
    string _suggestionLine;
    for (vector<CommandSpace>::iterator it = _registerCommands->begin(); it != _registerCommands->end(); ++it)
        _suggestionLine += it->command + ",";
    _suggestionLine = _suggestionLine.substr(0, _suggestionLine.length() - 1);
    _ioManager.PrintInput(_suggestionLine, 2);
    suggestionLine = "";
}

string CommandEngine::_getLine() 
{
    string writtenLine;
    I_IOManager::ReadResult readResult;

    while (true)
    {
        readResult = _ioManager.getLine(writtenLine);

        if (readResult == I_IOManager::IOM_COMPLETE) {
            _ioManager.PrintInput(writtenLine, 0);
            break;
        }

        if (readResult == I_IOManager::IOM_TAB)
            Complete(writtenLine);

        if (readResult == I_IOManager::IOM_START_TAB)
            StartOfTAB(writtenLine);
    }

    return writtenLine;
}

void CommandEngine::Run(string& inputString, bool cmd) 
{
    cout << "Dictionary [Version 2.1.01]\n<c> Enter help for acquainted with commands.\n\nDictionary>";

    while (_run) 
    {
        string beginstring;
        bool check = false;
        if (cmd)
            beginstring = inputString;
        else
            beginstring = _getLine();

        string delimiter = " ";
        vector<string> subStringVect;
        string suggestionString = beginstring;
        _ioManager.Split(subStringVect, beginstring, delimiter);
        bool suggestion = false;
        string result, commandName;
        pair<bool, CommandHandler *> headerBool;

        headerBool = FindCommand(subStringVect, _registerCommands);
        if (!headerBool.first) {
            if (Suggestion(suggestionString, commandName)) {
                _ioManager.PrintOutput("SUGGESTIONCOMMAND", commandName);
                _continue = true;
            }
            if (_continue)
                continue;
            _ioManager.PrintOutput("ERRORCOMMAND", "");
        }
        else if (!FindFlags(subStringVect, headerBool.second))
            _ioManager.PrintOutput("ERRORFLAG", "");
        else {
            headerBool.second->Execute(subStringVect, headerBool.second->GetFlag(), result);
            _ioManager.PrintOutput("RESULT", result);
        }

        _ioManager.PrintOutput("", "");

        if (cmd)
            break;
    }
    PostMessage(GetConsoleWindow(), WM_CLOSE, 0, 0);
}

