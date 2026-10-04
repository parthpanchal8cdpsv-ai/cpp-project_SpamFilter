#ifndef NAIVE_BAYES_H
#define NAIVE_BAYES_H

#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <set>
#include <map>
#include <vector>
#include <unordered_set>
#include <cmath>

#include "tokeniser.h"
using namespace std;

class Naive_Bayes{
    private:
        map<string,int>spam_freq; 
        map<string,int>ham_freq;

        int spam_freq_total=0;  
        int ham_freq_total=0;
        
        float p_mailIsSpam=0; 
        float p_mailIsHam=0;

        

    public:
        Naive_Bayes(const vector<Document>&docs);
            
        float p_wordInSpam(string wrd);

        float p_wordInHam(string wrd);
        
        string predict(const vector<string>&new_email);      
};
#endif
