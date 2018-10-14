/*
Author: Nick Szewczak
Course: CSCI-136
Instructor: Subhadarshi Panda
Assignment: Project 2 phase 2 Pesudocode
Task:
User enters a word — the program reports pronunciation as a list of phonemes AND a list of words that sound the same (is made up of exactly the same sequence of phonemes). Example:

> donut

Pronunciation    : D OW1 N AH2 T

Identical        : DOUGHNUT

...*/


#include <iostream>  //for cmd in out
#include <fstream>  //for file streaming
#include <climits>  //for max min opps
#include <array>    //array.size()

using namespace std;
//global
ifstream cmudict;

bool checkword(string word){
    bool pass = true;
    for(int i=0; i<word.length();i++){
        if(word[i]=='('){
            pass = false;
            break;
        }
    }
    return pass;
}

int phonemeCount(string pronounce){// returns the length of the phoneme array
    int spaces=1;
    for(int i=0; i < pronounce.length(); i++){ 
        if(pronounce[i]==' '){
            spaces++;
        }
    }
    return spaces;
}

string uppercase(string& word) {
  for (int i = 0; i < word.length(); i++) {
    word[i] = toupper(word[i]);
  }
  return word;
}

ifstream streamManager(){   //opens a stream to the dictionary file
    ifstream cmu("cmudict.0.7a");
        if (cmu.fail()) {
            cerr << "Dict file not found! Exiting \n";
            exit(1);
        }
    return cmu;
}

string findWord (string inputWord) {//parses through dict and returns pronounce string
    cmudict.clear();
    cmudict.seekg(0, ios::beg);
    string pronounce;
    string targetWord;
    while(cmudict >> targetWord){
        if(inputWord==targetWord){
            getline(cmudict, pronounce);
            break;
        }   
        else cmudict.ignore(INT_MAX, '\n'); //skips to the end of line
    }
    if (cmudict.fail()) {
    cerr << "Not found" << endl;
    exit(1); // exit if failed to open the file
    }
    string trimPronounce = pronounce.substr(1,pronounce.length());  //removes leading 2 spaces

    cout << "Pronunciation    :" << trimPronounce << endl;
    return pronounce;
}

void identicalPhoneme(string apronounce, string aword) { //creates string of identical words to pronounce key
    cmudict.clear();
    cmudict.seekg(0, ios::beg);
    string out = "Identical        :";
    for(int i=0; i < 118; ++i){ //skips header
    cmudict.ignore(INT_MAX, '\n');
    }
    string bword;
    string bpronounce;
    while(cmudict >> bword){
        getline(cmudict, bpronounce);
        if(bpronounce==apronounce && aword != bword && checkword(bword)){
            out = out + " " + bword;
        }
    }
    cout << out << endl;
}

void addPhoneme(string apronounce){
    apronounce = apronounce.substr(2,apronounce.length());  //removes leading 2 spaces
    int aArraySize = phonemeCount(apronounce);
    string aArray[20]; //blank array of apronounce
    int index = 0;

    for(int i=0; i<apronounce.length(); i++){
        if(apronounce[i] == ' '){
            index++;
        }
        else{
            aArray[index] = aArray[index] + apronounce[i];
        }
    }
    cmudict.clear();
    cmudict.seekg(0, ios::beg);
    string out = "Add phoneme      :";
    for(int i=0; i < 118; ++i){ //skipps header
    cmudict.ignore(INT_MAX, '\n');
    }
    string bword;
    string bpronounce;
    int bArraySize = 0;
    while(cmudict >> bword){
        getline(cmudict, bpronounce);
        bpronounce = bpronounce.substr(2,bpronounce.length());  //removes leading 2 spaces
        bArraySize = phonemeCount(bpronounce);
        if(aArraySize + 1 == bArraySize){
            string bArray[20]; //blank array of apronounce
            int indexb = 0;
            for(int i=0; i<bpronounce.length(); i++){  //creates bArray
                if(bpronounce[i] == ' '){
                    indexb++;
                }
                else{
                    bArray[indexb] = bArray[indexb] + bpronounce[i];
                }
            }
            int replaceCount = 0;
            int aindex = 0;
            for(int i=0; i < bArraySize; i++){  //now that we have two arrays of same length to compare:
                if(aArray[aindex] != bArray[i]){     //if array items do not equal,
                    replaceCount++;             //increment count
                }
                else{
                    aindex++;
                }
            }
            if(replaceCount == 1 && checkword(bword)){
                out = out + " " + bword;
            }
        }
    }
    cout << out << endl;
}

void removePhoneme(string apronounce){
    apronounce = apronounce.substr(2,apronounce.length());  //removes leading 2 spaces
    int aArraySize = phonemeCount(apronounce);
    string aArray[20]; //blank array of apronounce
    int index = 0;
    for(int i=0; i<apronounce.length(); i++){
        if(apronounce[i] == ' '){
            index++;
        }
        else{
            aArray[index] = aArray[index] + apronounce[i];
        }
    }
    cmudict.clear();
    cmudict.seekg(0, ios::beg);
    string out = "Remove phoneme   :";
    for(int i=0; i < 118; ++i){ //skipps header
    cmudict.ignore(INT_MAX, '\n');
    }
    string bword;
    string bpronounce;
    int bArraySize = 0;
    while(cmudict >> bword){
        getline(cmudict, bpronounce);
        bpronounce = bpronounce.substr(2,bpronounce.length());  //removes leading 2 spaces
        bArraySize = phonemeCount(bpronounce);
        if(aArraySize -1 == bArraySize){
            string bArray[20]; //blank array of apronounce
            int indexb = 0;
            for(int i=0; i<bpronounce.length(); i++){  //creates bArray
                if(bpronounce[i] == ' '){
                    indexb++;
                }
                else{
                    bArray[indexb] = bArray[indexb] + bpronounce[i];
                }
            }
            int replaceCount = 0;
            int bindex = 0;
            for(int i=0; i <= bArraySize; i++){  //now that we have two arrays to compare:
                // cout << aArray[i] << "[" << i << "]" << "\t\t" << bArray[bindex] <<"[" << bindex << "]" <<"\t"<< replaceCount << endl;
                if(aArray[i] != bArray[bindex]){     //if array items do not equal,
                    replaceCount++;             //increment count
                }
                else{
                    bindex++;
                }
            }
                if(replaceCount == 1 && checkword(bword)){
                // cout << bword << "[" <<replaceCount << "]"<< endl;
                out = out + " " + bword;
            }
        }
    }
    cout << out << endl;
}

void replacePhoneme (string apronounce) { //creates string of identical words to pronounce key
    apronounce = apronounce.substr(2,apronounce.length());  //removes leading 2 spaces
    int aArraySize = phonemeCount(apronounce);
    string aArray[20]; //blank array of apronounce
    int index = 0;
    for(int i=0; i<apronounce.length(); i++){
        if(apronounce[i] == ' '){
            index++;
        }
        else{
            aArray[index] = aArray[index] + apronounce[i];
        }
    }
    cmudict.clear();
    cmudict.seekg(0, ios::beg);
    string out = "Replace phoneme  :";
    for(int i=0; i < 118; ++i){ //skipps header
    cmudict.ignore(INT_MAX, '\n');
    }
    string bword;
    string bpronounce;
    int bArraySize = 0;
    while(cmudict >> bword){
        getline(cmudict, bpronounce);
        bpronounce = bpronounce.substr(2,bpronounce.length());  //removes leading 2 spaces
        bArraySize = phonemeCount(bpronounce);
        if(aArraySize==bArraySize){
            string bArray[20]; //blank array of apronounce
            int indexb = 0;
            for(int i=0; i<bpronounce.length(); i++){
                if(bpronounce[i] == ' '){
                    indexb++;
                }
                else{
                    bArray[indexb] = bArray[indexb] + bpronounce[i];
                }
            }
            int replaceCount = 0;
            for(int i=0; i < aArraySize; i++){  //now that we have two arrays of same length to compare:
                if(aArray[i] != bArray[i]){     //if array items do not equal,
                    replaceCount++;             //increment count
                }
            }
            if(replaceCount == 1 && checkword(bword)){
                out = out + " " + bword;
            }
        }
    }
    cout << out << endl;
}

int main(){
    string input;
    cin >> input;
    uppercase(input);
    cmudict = streamManager();
    string userPronounce = findWord(input);
    cout << endl;
    identicalPhoneme(userPronounce,input);
    addPhoneme(userPronounce);
    removePhoneme(userPronounce);
    replacePhoneme(userPronounce);
}

