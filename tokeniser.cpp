#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <set>
#include <map>
#include <vector>
#include <unordered_set>
#include "tokeniser.h"
using namespace std;

Document::Document(string Doclabel, vector<string> doctext){
    text=doctext;
    label=Doclabel;
    for(string present : doctext){
        if (!present.empty()) {             
            wordCount[present]++;       // If the word isn't empty after stripping punctuation, add it to the map
        }
    }

}

void Vocabulary::add_element(vector<string>sentence){
    for(string word:sentence){
        words.insert(word);
    }
}

void Vocabulary::show(){
    cout<<"all the words are:";
    for(string s:words){
        cout<<s<<endl;
    }
}

vector<string> SimpleTokeniser::tokenize(const string&text){
    vector<string>sentence;
    stringstream stream(text);                   //when ur reading a file, or doing cin, the string is passed as a stream so that we can go letter by letter, this converts into stream
    string word;


    while (stream >> word) {  /*automatically splits the data at whitespaces and while()
                              and checks if there is a word still or is it done*/
        string cleanedWord = cleanedword(word);
        sentence.push_back(cleanedWord);        
    }


    if(sentence.empty()){
        return sentence; /*So that in the next step we dont try to access 0th element of an empty sentence*/
    }
    string label=sentence[0];              //first word is always the label

    sentence.erase(sentence.begin());          //removing the label

    bigram_maker(sentence); /*This appends pairs of words to sentence*/
     /*After applying this , the  rest of the logic of our program remains the same , its just that the sentence vector is now bigger.*/

    Document d1(label,sentence);
    all_docs.push_back(d1);
    v1.add_element(sentence);

    return sentence;
}

vector<string> StopWordTokeniser::tokenize(const string& text){   
        vector<string>sentence;
        stringstream stream(text);  
        string word;
        
        while (stream >> word) {               
            string cleaned = cleanedword(word);
            if (!cleaned.empty() && stop_words.find(cleaned) == stop_words.end()) { //if the word is not in the stop_words, add to sentence
                sentence.push_back(cleaned);
            }       
        }

        string label=sentence[0];    

        sentence.erase(sentence.begin());  

        bigram_maker(sentence); /*This appends pairs of words to sentence*/
        /*After applying this , the  rest of the logic of our program remains the same , its just that the sentence vector is now bigger.*/
                 
        Document d1(label,sentence);
        all_docs.push_back(d1);
        v1.add_element(sentence);

        return sentence;
}  