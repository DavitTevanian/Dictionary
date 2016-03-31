#ifndef _I_IOMANAGER_
#define _I_IOMANAGER_

#include <vector>
#include <string>
using namespace std;

class I_IOManager 
{
public:
    enum ReadResult { IOM_TAB, IOM_START_TAB, IOM_COMPLETE };

    virtual bool       QueryUser(const string& query, string& answer) = 0;
    virtual ReadResult getLine(string& inputString) = 0;
    virtual void       Split(vector<string>& vectInputString, string& inputString, string& delimiter) = 0;
    virtual void       PrintInput(const string& inpurString, int check) = 0;
    virtual void       PrintOutput(const string& checkString, const string& fartherString) = 0;
    virtual bool       StartLog(const string& logFile) = 0;
    virtual bool       EndLog() = 0;
    virtual void       Print() = 0;
    virtual void       StartSilent() = 0;
    virtual void       StopSilent() = 0;

protected:
    ~I_IOManager() {};
};

#endif// _I_IOMANAGER_