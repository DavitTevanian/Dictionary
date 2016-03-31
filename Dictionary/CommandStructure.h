#ifndef _COMMANDSTRUCTURE_
#define _COMMANDSTRUCTURE_

#include "CommandHandler.h"
#include <string>

struct CommandSpace
{
    CommandHandler* handler;
    string          command;
};

#endif _COMMANDSTRUCTURE_