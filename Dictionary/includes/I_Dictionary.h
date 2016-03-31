#ifndef _I_DICTIONARY_
#define _I_DICTIONARY_

#include <map>
#include <string>
#include <vector>
using namespace std;

class I_Dictionary{

public:
	virtual void Start()=0;
	virtual void End()=0;
	virtual void Split( vector<string> & vect,string & str,string & delim)=0;
	virtual string Translate(const string & word)=0;
	virtual string AddWord(const string & word,const string & translation)=0;
	virtual string Delete(const string & word)=0;
	virtual string DeleteByFlag(const string & word,const string & translation)=0;
	virtual string Append(const string & word,const string & translation)=0;
	virtual string Replace(const string & word,const string & translation)=0;
	virtual int Count()const=0;
	virtual  string PrintAll()=0;
	virtual string RemoveAll()=0;
	virtual void ProcessIndicator(int count)=0;
protected:
	virtual ~I_Dictionary() {};
};

#endif //_I_DICTIONARY_