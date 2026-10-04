#ifndef FILE_IO_H
#define FILE_IO_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "tokeniser.h"
using namespace std;

// True if the line has at least one word left after cleaning punctuation.
// Guards against lines like "   " or "..." that would make tokenize() crash on sentence[0].
inline bool has_content(const string& line)
{
    stringstream sentence(line);
    string word;
    while (sentence >> word) {
        if (!cleanedword(word).empty()) return true;
    }
    return false;
}

// Reads a file where each line is:  <label> <message text>
// Feeds every usable line to the tokeniser (which fills all_docs and v1).
// Returns number of lines loaded, or -1 if the file couldn't be opened.
inline int load_training_file(const string& filename, ITokeniser& tokeniser)
{
    ifstream file(filename);          //fopen of cpp
    if (!file.is_open()) {
        throw runtime_error("Error: could not open training file");
    }

    string line;
    int count = 0;
    while (getline(file, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();  // Windows line endings
        if (!has_content(line)) continue;                           // blank / punctuation-only
        tokeniser.tokenize(line);
        count++;
    }
    return count;  // ifstream closes itself when it goes out of scope
}


#endif
