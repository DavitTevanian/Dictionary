#include "Dictionary.h"

#include <utility>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <conio.h>
#include <time.h>
#include <Windows.h>

Dictionary::Dictionary() {}

Dictionary::~Dictionary() {}

int Dictionary::count = 0;

void Dictionary::Split(vector<string>& vect, string& str, string& delim) 
{
    size_t pos = 0;
    string temp;
    while ((pos = str.find(delim, 0)) != string::npos) {
        temp = str.substr(0, pos);
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        vect.push_back(temp);
        str.erase(0, pos + delim.length());
    }
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    vect.push_back(str);
}

void Dictionary::Start() 
{
    ifstream infile1("Count");

    if (!infile1.good()) {
        cerr << "Can't read the file" << endl;
    }

    while (!infile1.eof()) {
        infile1 >> count;
    }
    infile1.close();

    ifstream infile("Dictionary");

    if (!infile.good()) {

        cerr << "Can't read the file" << endl;
    }

    string str;
    vector<string> vect;
    string delimiter = "-";

    while (!infile.eof()) {
        getline(infile, str);
        Split(vect, str, delimiter);
    }
    pair<map<string, string>::iterator, bool> ret;
    for (size_t i = 0; i < (vect.size() / 2); ++i) {
        ret = dict.insert(make_pair(vect[i * 2], vect[i * 2 + 1]));
        if (!ret.second)
            cout << "The word didn't insert!" << endl;
    }
    infile.close();
}

void Dictionary::End() 
{
    ofstream outfile1("Count", ios_base::trunc);
    if (!outfile1.good()) {
        cerr << "Can't write the file" << endl;
    }
    outfile1 << Count();
    outfile1.close();
    ofstream outfile("Dictionary", ios::trunc);

    if (!outfile.good()) {
        cerr << "Can't write the file" << endl;
    }

    for (map<string, string>::iterator it = dict.begin(); it != dict.end(); ++it) {
        outfile << it->first << "-" << it->second;
        outfile << "\n";
    }

    outfile.close();
}

void Dictionary::ProcessIndicator(int count) 
{
    int i = 0;

    cout << endl << "Loading... ";

    while (i <= 100) {

        Sleep(count);
        cout << i << " % ";
        if (i < 10) {
            for (int i = 0; i < 4; ++i)
                _putch(8);
        }
        else if (i < 100) {
            for (int i = 0; i < 5; ++i)
                _putch(8);
        }
        else {
            for (int i = 0; i < 6; ++i)
                _putch(8);
        }
        i++;
    }
    if (i != 100) {
        cout << 100 << " % ";
    }
    cout << endl;
}

int Dictionary::Count()const 
{
    return count;
}

string Dictionary::AddWord(const string& key, const string& meaning) 
{
    pair<map<string, string>::iterator, bool> ret;
    ret = dict.insert(make_pair(key, meaning));
    if (!ret.second)
        return "\nThe word didn't insert ";
    else {
        count++;
        End();
        return "\nAdded  ";
    }
}

string Dictionary::Delete(const string& key) 
{
    for (map<string, string>::iterator it = dict.begin(); it != dict.end(); ++it) {

        if (it->first == key) {
            dict.erase(key);
            count--;
            End();
            return "\nDeleted  ";
        }
        if (it->second == key) {
            dict.erase(it->first);
            count--;
            End();
            return "\nDeleted  ";
        }
    }
    return "\nDictionary doesn't contain this word  ";

}

string Dictionary::Translate(const string& key)
{
    for (map<string, string>::iterator it = dict.begin(); it != dict.end(); ++it) {
        if (it->first == key)
            return "\n[ " + it->second + " ]";
        if (it->second == key)
            return "\n[ " + it->second + " ]";
    }
    return "\nDictionary doesn't contain this word";
}

string Dictionary::PrintAll() 
{
    if (dict.empty())
        return "\nDictionary is empty ! ";
    else {
        string result;
        for (map<string, string>::iterator it = dict.begin(); it != dict.end(); ++it) {
            result += "  " + it->first + " - " + it->second + "\n";
        }
        return result;
    }
}

string Dictionary::RemoveAll() 
{
    dict.erase(dict.begin(), dict.end());
    if (dict.empty()) {
        End();
        count = 0;
        return "\nAll removed ";
    }
    else
        return "\nWas wrong ";
}

string Dictionary::Append(const string& word, const string& translation) 
{
    if (dict[word].empty()) {
        dict[word] = translation;
        count++;
        End();
        return "\nAdded,because dictionary didn't contanin such word";
    }
    dict[word] = dict[word] + "," + translation;
    End();
    return "\nAppended ";
}

string Dictionary::Replace(const string& word, const string& translation) 
{
    if (dict[word].empty()) {
        dict[word] = translation;
        count++;
        End();
        return "\nAdded,because dictionary didn't contanin such word ";
    }
    dict[word] = translation;
    End();
    return "\nReplaced ";
}

string Dictionary::DeleteByFlag(const string& word, const string& translation) 
{
    for (map<string, string>::iterator it = dict.begin(); it != dict.end(); ++it) {
        if (it->first == word) {
            size_t pos = it->second.find(translation);
            if (pos == string::npos)
                return "\nDon't exists such meaning ";
            if (it->second[pos + translation.length()] != ',')
                it->second.replace(pos - 1, translation.length() + 1, "");
            else
                it->second.replace(pos, translation.length() + 1, "");

            End();
            return "\nMeaning chosen deleted ";
        }
    }
    return "\nDictionary doesn't contain this word ";
}

