#include "ApplicationDictionary.h"

int main(int argc, char * argv[])
 {
    vector<string> cmdArgs(argv, argv + argc);
    ApplicationDictionary dictionary;
    dictionary.Run(argc, cmdArgs);
}
// remove me
