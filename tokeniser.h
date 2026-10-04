#ifndef TOKENISER_H
#define TOKENISER_H

#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <set>
#include <map>
#include <vector>
#include <unordered_set>
using namespace std;

inline string cleanedword(string present){
    string newword="";
    for(char c: present){
        if(!ispunct(c)){
            newword+=tolower(c);         
        }
    }
    return newword;
}

inline void bigram_maker(vector<string>&text){
    int n=text.size();
    if(n<2){
        return;
    }
    text.reserve(n+n-1);
    for(int i=1;i<n;i++){
        text.push_back(text[i-1]+"_"+text[i]);
    }

}

class Document {                             
public:
    vector<string> text;
    string label;
    map<string ,int> wordCount;
    Document(string Doclabel, vector<string> doctext);
};

extern vector<Document> all_docs;        

class Vocabulary{                         
public:
    set<string>words;
    void add_element(vector<string> sentence);
    void show();
};
extern Vocabulary v1;  

class ITokeniser {                                               
    public:
    virtual vector<string> tokenize(const string& text) = 0;            
    virtual ~ITokeniser() = default;
};

class SimpleTokeniser : public ITokeniser { 
    public:        
    vector<string> tokenize(const string& text);  
 };

class StopWordTokeniser : public ITokeniser {
    private:
    unordered_set<string> stop_words={
        "the", "is", "at", "which", "and", "a", "an", "in", "to", "it", "of", "for", "on", "with"
    };
    public:
    vector<string> tokenize(const string& text);
};

#endif