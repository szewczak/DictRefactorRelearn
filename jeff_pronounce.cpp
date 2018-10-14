/*
Author: Jeffrey Horn
Course: CSCI-136
Instructor: Subhadarshi Panda	
Assignment: phaseI.cpp

User enters a word, and the program only reports pronunciation as a list of phonemes. 
*/

#include <iostream> //cout for debugging
#include <fstream> //Filestream access
#include <cstdlib>
#include <string> //String methods
#include <climits> // max and min
#include <cctype> //isDigit
using namespace std;

string uppercase(string& word) {
  for (int i = 0; i < word.length(); i++) {
    word[i] = toupper(word[i]);
  }
  return word;
}

int arraySize(string target) {
  int spaces = 1;
  for (int i = 0; i < target.length(); i++) {
    // cout << target[i] << ",";
    if (target[i] == ' ') spaces++;
  }
  return spaces;
}

void splitOnSpace(string s, string& before, string& after) {
  // reset strings
  before = ""; 
  after = "";
  // accumulate before space
  int i = 0;
  while (i < s.size() && not isspace(s[i])) { before += s[i]; i++; }
  // skip the space
  i++;
  // accumulate after space
  while (i < s.size()) { after += s[i]; i++; }
}

bool wordValidation(string word) {
  for (int i = 0; i < word.length(); i++) {
    if (isdigit(word[i])) return false;
  }
  return true;
}

void phonemeManip(string targetPhoneme) {
  string replaceOut = "Replace phoneme : "; 
  string removeOut = "Remove phoneme : ";
  string addOut = "Add phoneme : ";
  targetPhoneme = targetPhoneme.substr(2, targetPhoneme.length());
  int tArrSize = arraySize(targetPhoneme);
  string tArr[20];
  int tArrIndex = 0;
  for (int i = 0; i < targetPhoneme.length(); i++) { //start at 1 to skip initial space
    if (targetPhoneme[i] == ' ') tArrIndex++;
    else tArr[tArrIndex] = tArr[tArrIndex] + targetPhoneme[i];
  }

  ifstream fin("cmudict.0.7a");
  if (fin.fail()) {
    cerr << "File cannot be opened for reading." << endl; //error handling, give error to terminal
    exit(1); //exit if failed to open file
  }
  for (int y = 0; y < 118; y++) {
    fin.ignore(INT_MAX, '\n');
  }
  string currentWord;
  string currentPhoneme;
  int cArrSize = 0; //current Array Size, will hold array size for comparison
  while(fin >> currentWord) {
    getline(fin, currentPhoneme);
    currentPhoneme = currentPhoneme.substr(2, currentPhoneme.length());
    cArrSize = arraySize(currentPhoneme);
    int cArrIndex;
    int comparisonCounter;
    string cArr[20];
    //replace phoneme
    if (cArrSize == tArrSize) {
      cArrIndex = 0;
      for (int j = 0; j < currentPhoneme.length(); j++) {
        if (currentPhoneme[j] == ' ') {
          cArrIndex++;
        } else {
          cArr[cArrIndex] = cArr[cArrIndex] + currentPhoneme[j];
        }
      }

      comparisonCounter = 0;
      for (int x = 0; x < cArrSize; x++) {
        if (tArr[x] != cArr[x]) {
          comparisonCounter++;
        }
      }
      if (comparisonCounter == 1) {
        if (wordValidation(currentWord)) {
          replaceOut = replaceOut + " " + currentWord;
        }
      }
    }
  
    //add phoneme
     else if (cArrSize == tArrSize+1) {
       cArrIndex = 0;
       for (int k = 0; k < currentPhoneme.length(); k++) {
         if (currentPhoneme[k] == ' ') {
           cArrIndex++;
         } else {
           cArr[cArrIndex] = cArr[cArrIndex] + currentPhoneme[k];
         }
       }
      comparisonCounter = 0;
      int tArrAddIndex = 0;
      for (int x = 0; x < cArrSize; x++) {
        if (cArr[x] != tArr[tArrAddIndex]) {
          comparisonCounter++;
        } else {
          tArrAddIndex++;
        }
      }
      if (comparisonCounter == 1) {
        if (wordValidation(currentWord)) {  
          addOut = addOut + " " + currentWord;
        }
      }
    } 

    //remove phoneme
    else if (cArrSize == tArrSize-1) {
      cArrIndex = 0;
      for (int p = 0; p < currentPhoneme.length(); p++) {
        if (currentPhoneme[p] == ' ') {
          cArrIndex++;
        } else {
          cArr[cArrIndex] = cArr[cArrIndex] + currentPhoneme[p];
        }
      }
      comparisonCounter = 0;
      int cArrRemIndex = 0;
      for (int x = 0; x < tArrSize; x++) {
        if (cArr[cArrRemIndex] != tArr[x]) {
          comparisonCounter++;
        } else {
          cArrRemIndex++;
        }
      }
      if (comparisonCounter == 1) {
        if (wordValidation(currentWord)) {
          removeOut = removeOut + " " + currentWord;
        }
      }
    }
  }
  cout << addOut << endl;
  cout << removeOut << endl;
  cout << replaceOut << endl;
}



int main () {
  string userword;
  cin >> userword;
  userword = uppercase(userword);


  string target;
  string currentPhoneme;
  string targetPhoneme;
  string before;
  string after;
  string identical_words = " ";
  bool targetFound = false;
  
  {
    ifstream fin("cmudict.0.7a");
    if (fin.fail()) {
      cerr << "File cannot be opened for reading." << endl; //error handling, give error to terminal
      exit(1); //exit if failed to open file
    }

    while (fin >> target) {
      if (target == userword) {
        getline(fin, currentPhoneme);
        targetPhoneme = currentPhoneme;
        targetFound = true;
        cout << "Pronunciation\t:" << targetPhoneme << endl;
      } else {
        fin.ignore(INT_MAX, '\n'); //skips to the end of line, ignoring remaining columns
      }
    }
  }

  {
    ifstream fin("cmudict.0.7a");
    if (fin.fail()) {
      cerr << "File cannot be opened for reading." << endl; //error handling, give error to terminal
      exit(1); //exit if failed to open file
    }
    while (fin >> target) {
      getline(fin, after);
      if (after == targetPhoneme && targetFound && target != userword) {
        identical_words = identical_words + target + " ";
      }
    }
  } 
  if (targetFound) {
    cout << endl;
    cout << "Identical\t: " << identical_words << endl;
    phonemeManip(targetPhoneme);
  } else {
    cout << "Not found";
  }
  return 0;
}