#ifndef _IOMANAGER_
#define _IOMANAGER_
#include "QueryInterface.h"
#include <fstream>
#include <vector>

class IOManager:public QueryInterface{

public:
	enum ReadResult {IOM_TAB,IOM_START_TAB,IOM_COMPLETE};

	friend class LogFileHandler;
	friend class SilentModeHandler;

	IOManager();
	bool QueryUser(const string & query,string & answer);
	ReadResult getLine(string & inputString);
	void Split( vector<string> & vectInputString,string & inputString,string & delimiter);
	void PrintInput(const string & inpurString,int check);
	void PrintOutput(const string & checkString,const string & fartherString);
	
private:
	ofstream f_out;
	ifstream f_in;
	vector<string> _history;
	bool log,silent,print;
};

#endif _IOMANAGER_