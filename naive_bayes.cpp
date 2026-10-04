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
#include "naive_bayes.h"
using namespace std;

Naive_Bayes::Naive_Bayes(const vector<Document>&docs){
    int spam_mails_total=0;
    int ham_mails_total=0;
    for(auto x:docs){
        /*For every document , if its a mail , then go through every word and increment the spam_freq  based on how many times it occured in that mail*/
        if(x.label=="spam"){
            spam_mails_total++;
            for(auto y:x.wordCount){
                spam_freq[y.first]=spam_freq[y.first]+y.second;
                
            }
        }
        else{
            ham_mails_total++;
            for(auto y:x.wordCount){
                ham_freq[y.first]=ham_freq[y.first]+y.second;
            }
        }
        
    }

    

    for(auto z:spam_freq){
        spam_freq_total=spam_freq_total+z.second;
    }
    for(auto z:ham_freq){
        ham_freq_total=ham_freq_total+z.second;
    }

    p_mailIsSpam=spam_mails_total/(float)(spam_mails_total+ham_mails_total);
    p_mailIsHam=1.0-p_mailIsSpam;
}

float Naive_Bayes::p_wordInSpam(string wrd){
    float spam_freq_wrd=0;
    if(spam_freq.count(wrd)>0){
        spam_freq_wrd=spam_freq[wrd];
    }
    
    return (spam_freq_wrd+1)/(float)((spam_freq_total)+(v1.words.size())); 
    /*Here were using Laplace smoothing , adding the one to prevent probabilities from going 0 when the word frequency is 0
    ( but cuz of that extra 1 in numerator we need to tune up the denominator for normalizing the prob)*/
    
}

float Naive_Bayes::p_wordInHam(string wrd){
    float ham_freq_wrd=0;
    if(ham_freq.count(wrd)>0){
        ham_freq_wrd=ham_freq[wrd];
    }
    return (ham_freq_wrd+1)/(float)((ham_freq_total)+(v1.words.size()));
}

string Naive_Bayes::predict(const vector<string>&new_email){

    /*naive bayes formula is : p(class|mail)=(p(mail|class)xp(class))/(p(mail))  , mail given class means(we apply laplace smoothing to it btw) , given that youre looking in spam/ham folder ,whats the chance youll find the words from the mail in the folder
    p(class) is the general prob of a mail being the spam or ham ( total spams/ total mails) , p(mail) is (for every word) do:  how many mails has it occured in divide by total mails         */

    /* We dont find p(mail) since for both classes it would have the same value
        We find spam score and ham score by ignoring p(mail) and taking log on both sides to avoid small values*/

    /*Now applying the formula*/
    float spam_score=log(p_mailIsSpam);
    float ham_score=log(p_mailIsHam);

    for(auto x:new_email){
        spam_score=spam_score+log(p_wordInSpam(x));
        ham_score=ham_score+log(p_wordInHam(x));
    }

    if(spam_score>ham_score){
        return "spam";
    }
    else{
        /*Even if spamscore=hamscore , we should return "ham"  cuz its better to mark a spam as ham rather than marking an imp ham email as spam*/
        return "ham";
            }
    } 
