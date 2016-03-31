#ifndef _QUERYINTERFACE_
#define _QUERYINTERFACE_
#include <string>
using namespace std;
 
class QueryInterface{
public:
	virtual bool QueryUser(const string & query,string & answer)=0;
protected:
	virtual ~QueryInterface() {};
};

#endif // _QUERYINTERFACE_