#ifndef  _AUTOCOMPLETE_
#define  _AUTOCOMPLETE_

#include "includes\CommandStructure.h"
#include <string>
#include <vector>
using namespace std;

class AutoComplete 
{
public:
    vector<string> Autocomplete(const vector<CommandSpace>* commands, const string& substring);
};

#endif // _AUTOCOMPLETE_