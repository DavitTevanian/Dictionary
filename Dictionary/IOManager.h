#ifndef _IOMANAGER_
#define _IOMANAGER_
#include "includes\QueryInterface.h"
#include "includes\I_IOManager.h"
#include <fstream>


class IOManager : public QueryInterface, public I_IOManager 
{
public:

    IOManager();
    ~IOManager();
    bool       QueryUser(const string& query, string& answer);
    ReadResult getLine(string& inputString);
    void       Split(vector<string>& vectInputString, string& inputString, string& delimiter);
    void       PrintInput(const string& inpurString, int check);
    void       PrintOutput(const string& checkString, const string& fartherString);
    bool       StartLog(const string& logFile);
    bool       EndLog();
    void       Print(const string& logFile);
    void       StartSilent();
    void       StopSilent();

private:
    ofstream       f_out;
    ifstream       f_in;
    vector<string> _history;
    bool           log;
    bool           silent;
};

#endif //_IOMANAGER_