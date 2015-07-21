//
// Created by arkezar on 15.07.15.
//

#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

void genWord(list<char> chars, vector<string>& words, const string& word){
    if(chars.size() == 0){
        words.push_back(word);
    } else {
        string tmpWord;
        for (const auto &c : chars) {
            tmpWord = word+c;
            auto tmpChars = chars;
            tmpChars.remove(c);
            genWord(tmpChars, words, tmpWord);
        }
    }
}



int main(int argc, char *argv[]) {
    ifstream stream(argv[1]);
//    ifstream stream("/home/arkezar/permut");
    string line;

    list<char> chars;
    vector<string> words;

    while (getline(stream, line)) {
        for(const auto& c : line)
            chars.push_back(c);

        genWord(chars,words,"");

        sort(words.begin(),words.end());

        for(int i = 0 ; i < words.size() ; i++){
            cout << words[i];
            if(i!=words.size()-1)
                cout << ",";
            else
                cout << endl;
        }

        words.clear();
        chars.clear();
    }
    return 0;
}