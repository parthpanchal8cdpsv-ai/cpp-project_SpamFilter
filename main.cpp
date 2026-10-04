#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>


#include "tokeniser.h"
#include "naive_bayes.h"
#include "file_io.h"

using namespace std;

// global definitions required by tokeniser.h
vector<Document> all_docs;
Vocabulary v1;

int main() {
    string filename;
    //cout << "Enter the text file name (like data.txt): ";
    //cin >> filename;

    StopWordTokeniser s1; 
    
    try{
        /*Load the .txt file*/
        int loaded_count = load_training_file("uci_sms_dataset.txt", s1);
        cout << "Loaded " << loaded_count << " documents." << endl;
    } 
    catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }

    /*Shuffling the docs*/
    random_device rd;
    mt19937 g(rd());
    shuffle(all_docs.begin(), all_docs.end(),g);

    /*80-20 split*/
    int split_idx = all_docs.size()*0.8;

    vector<Document>train_docs;
    vector<Document>test_docs;
    for(int i=0;i<split_idx;i++){
        train_docs.push_back(all_docs[i]);
    }
    for(int i=split_idx;i<all_docs.size();i++){
        test_docs.push_back(all_docs[i]);
    }
    Naive_Bayes nb1(train_docs);

    /*Declaring true positive , false negative etc counters */
    /*Im considering that "positive" means that "yes , its a spam" , since the goal is spam detection...*/ 
    int tp=0;
    int fp=0;
    int tn=0;
    int fn=0;

    for(auto doc:test_docs){
        string truelabel=cleanedword(doc.label);
        string predlabel=cleanedword(nb1.predict(doc.text));
        if(predlabel==truelabel){
            if(predlabel=="spam"){
                tp++;
            }
            else{
                tn++;
            }
        }
        else{
            if(predlabel=="spam"){
                fp++;
            }
            else{
                fn++;
            }
        }

    }

    float precision=tp/(float)(tp+fp+0.001); /*means , out of all the mails that u declared as spam , how many were actually spam*/
    float recall=tp/(float)(tp+fn+0.001); /*means , out of all the total actual spams , how many could you pick out */
    float accuracy=(tp+tn)/(float)(tp+tn+fp+fn+0.001); /*what all did your model do correctly */
    float f1score=2*((precision*recall)/(float)(precision+recall)); /*shows how balanced precision and recall is */

    /*The main one here is precision , if precision is low it means you are declaring important hams as spams , which is very bad*/
    cout<<"     MODEL METRICS -   "<<endl;
    cout<<"Precision: "<<precision*100<<"%"<<endl;
    cout<<"Recall:"<<recall*100<<"%"<<endl;
    cout<<"Accuracy: "<<accuracy*100<<"%"<<endl;
    cout<<"F1 Score:"<<f1score*100<<"%"<<endl;

    string text;
    cout<<"enter email u want to see classified"<<endl;
    getline(cin,text);
    vector<string> tokens = s1.tokenize(text);

    string prediction = nb1.predict(tokens);
    cout<<text<<" is predicted as "<<prediction;




    return 0;
}