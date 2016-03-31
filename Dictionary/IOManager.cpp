#include "IOManager.h"
#include "includes\CommandStructure.h"
#include <conio.h>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
using namespace std;

#define BACKSPACE 8
#define TAB 9
#define ENTER 13
#define ARROW_UP 72
#define ARROW_LEFT 75
#define ARROW_RIGHT 77
#define ARROW_DOWN 80

IOManager::IOManager() : log(false), silent(false) {}

void IOManager::Split(vector<string>& vectInputString, string& inputString, string& delimiter) 
{
    size_t pos = 0;
    string temp;
    while ((pos = inputString.find(delimiter, 0)) != string::npos) {

        temp = inputString.substr(0, pos);
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        vectInputString.push_back(temp);
        inputString.erase(0, pos + delimiter.length());
    }
    transform(inputString.begin(), inputString.end(), inputString.begin(), ::tolower);
    vectInputString.push_back(inputString);
}

bool IOManager::StartLog(const string& logFile) 
{
    f_out.open(logFile, ios::trunc);
    if (f_out.is_open()) {
        const time_t currentTime = time(NULL);
        char timeString[26];
        ctime_s(timeString, 26, &currentTime);
        f_out << setw(70) << setfill(' ') << timeString << "\n";
        log = true;
        return true;
    }
    return false;
}

bool IOManager::EndLog() 
{
    f_out.close();
    if (f_out.is_open())
        return false;
    else {
        log = false;
        return true;
    }
}

void IOManager::Print(const string& logFile) 
{
    f_in.open(logFile);
    if (f_in.is_open()) {
        while (!f_in.eof())
        {
            string line;
            getline(f_in, line);
            cout << line;
        }
    }
    else
        cout << "\nFile" + logFile + "didn't open !\n";
}

void IOManager::StartSilent() 
{
    silent = true;
}

void IOManager::StopSilent() 
{
    silent = false;
}

bool IOManager::QueryUser(const string& query, string& answer) 
{
    if (silent == false) {
        cout << query;

        char simbol;
        string tempAnswer;

        while ((simbol = _getch()) != ENTER) {
            _putch(simbol);
            tempAnswer += simbol;
        }
        answer = tempAnswer;
        if (log) {
            f_out << query;
            f_out << answer << endl;
        }
        transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
        return true;
    }
    return false;
}

void IOManager::PrintOutput(const string& checkString, const string& fartherString) 
{

    if (checkString == "ERRORCOMMAND") {
        cout << "\nDictionary doesn't contain such command !\nPlease enter correct command \n";
        if (log) {
            f_out << "\nDictionary doesn't contain such command !\nPlease enter correct command \n";
        }
    }
    else if (checkString == "ERRORFLAG") {
        cout << "\nThis command doesn't contain such flag !\nPlease enter correct flag \n";
        if (log) {
            f_out << "\nThis command doesn't contain such flag !\nPlease enter correct flag \n";
        }
    }
    else if (checkString == "SUGGESTIONCOMMAND") {
        cout << "\nDictionary doesn't contain such command !\nMaybe you are mean [ " + fartherString + " ] ?\nDictionary>";
        if (log)
            f_out << "\nDictionary doesn't contain such command !\nMaybe you are mean [ " + fartherString + " ] ?\nDictionary>";
    }
    else if (checkString == "RESULT") {
        cout << fartherString << endl;
        if (log)
            f_out << fartherString << endl;
    }
    else {
        cout << "Dictionary>";
        if (log)
            f_out << "Dictionary>";
    }

}
void IOManager::PrintInput(const string& inpurString, int check) 
{

    if (check == 0) {
        if (log)
            f_out << inpurString << "\n";
        cout << "\n";
    }
    if (check == 1) {
        if (log)
            f_out << inpurString;
        cout << inpurString;
    }
    if (check == 2) {
        if (log)
            f_out << inpurString << "\nDictionary>";
        cout << inpurString << "\nDictionary>";
    }
}


IOManager::ReadResult IOManager::getLine(string& inputString) 
{
    char simbol;
    unsigned xPos = inputString.size(), yPos = 0;

    while ((simbol = _getch()) != ENTER) {

        if (simbol == TAB) {
            if (xPos == 0)
                return IOM_START_TAB;
            return IOM_TAB;
        }
        else if (simbol < 0) {
            simbol = _getch();
            if (simbol == ARROW_UP && !_history.empty()) {
                yPos--;
                if (yPos > _history.size())
                    yPos = _history.size();
                for (size_t k = 0; k < inputString.size(); ++k) {
                    _putch(8);
                    _putch(32);
                    _putch(8);
                }
                inputString = "";
                if (yPos)
                    inputString = _history[yPos - 1];
                xPos = inputString.size();
                cout << inputString;
            }
            else if (simbol == ARROW_DOWN && !_history.empty()) {
                yPos++;
                if (yPos > _history.size())
                    yPos = 0;
                for (size_t k = 0; k < inputString.size(); ++k) {
                    _putch(8);
                    _putch(32);
                    _putch(8);
                }
                inputString = "";
                if (yPos)
                    inputString = _history[yPos - 1];
                xPos = inputString.size();
                cout << inputString;
            }
            else if (simbol == ARROW_LEFT && xPos > 0) {
                _putch(8);
                xPos--;
            }
            else if (simbol == ARROW_RIGHT && xPos < inputString.size()) {
                cout << inputString[xPos++];
            }
        }
        else if (simbol == BACKSPACE) {
            if (xPos == 0) {
                cout << inputString[xPos];
                _putch(8);
            }
            else if (xPos != inputString.size()) {
                _putch(8);
                _putch(32);
                _putch(8);
                cout << inputString.substr(xPos);
                _putch(32);
                xPos--;
                inputString = inputString.substr(0, xPos) + inputString.substr(xPos + 1);
                for (size_t i = 0; i < inputString.substr(xPos).size() + 1; ++i)
                    _putch(8);

            }
            else {
                _putch(8);
                _putch(32);
                _putch(8);
                inputString = inputString.substr(0, inputString.size() - 1);
                xPos--;
            }
        }
        else {
            string temp = inputString.substr(xPos);
            _putch(simbol);
            cout << temp;
            for (size_t i = 0; i < inputString.substr(xPos).size(); ++i)
                _putch(8);
            inputString = inputString.substr(0, xPos) + simbol + temp;
            xPos++;
        }
    }

    bool exist = false;
    for (size_t i = 0; i < _history.size(); ++i) {
        if (_history[i] == inputString) {
            exist = true;
            break;
        }
    }
    if (!exist) {
        _history.push_back(inputString);
    }

    return IOM_COMPLETE;
}

IOManager::~IOManager() { }
