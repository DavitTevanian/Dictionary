#ifndef _DICTIONARY_
#define _DICTIONARY_

#include "includes\I_Dictionary.h"
#include <map>
#include <string>
#include <vector>
using namespace std;

class Dictionary :public I_Dictionary 
{
public:
    Dictionary();
    ~Dictionary();
    void   Start();
    void   End();
    void   Split(vector<string>& vect, string& str, string& delim);
    string Translate(const string& word);
    string AddWord(const string& word, const string& translation);
    string Delete(const string& word);
    string DeleteByFlag(const string& word, const string& translation);
    string Append(const string& word, const string& translation);
    string Replace(const string& word, const string& translation);
    string PrintAll();
    string RemoveAll();
    int    Count()const;
    void   ProcessIndicator(int count);

private:
    map<string, string> dict;
    static int count;
};

#endif //_DICTIONARY_