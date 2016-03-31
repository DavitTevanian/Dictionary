#include "AutoComplete.h"
#include "includes\CommandHandler.h"
#include <iostream>

vector<string> AutoComplete::Autocomplete(const vector<CommandSpace>* commands, const string& substring) 
{
    vector<string> autoCompleteVect;
    for (vector<CommandSpace>::const_iterator it = commands->begin(); it != commands->end(); ++it) {
        if (it->command.find(substring) == 0) {
            autoCompleteVect.push_back(it->command.substr(substring.length()));
        }

        if (substring.size() >= 6 && it->command.find(substring.substr(5)) == 0)
            autoCompleteVect.push_back(it->command.substr(substring.substr(5).length()));

    }
    for (size_t pos = 0; pos < substring.size(); ++pos) {
        if (substring[pos] == '-') {
            string commandWithoutAC;
            size_t tempPos = substring.find(" ", 0);
            commandWithoutAC = substring.substr(0, tempPos);

            for (vector<CommandSpace>::const_iterator it = commands->begin(); it != commands->end(); ++it) {
                if (it->command == commandWithoutAC) {
                    for (size_t i = 0; i < it->handler->GetFlag().size(); ++i) {
                        if (substring[pos + 1] == it->handler->GetFlag()[i].flagName.at(1))
                            autoCompleteVect.push_back(it->handler->GetFlag()[i].flagName.substr(substring.length() - pos));
                    }
                }
            }
        }
    }

    return autoCompleteVect;
}

