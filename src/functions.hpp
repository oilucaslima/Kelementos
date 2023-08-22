#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include "library.hpp"

using namespace std;

void updateWord(string word, map <string,int> &wordHash, unordered_map <string,int> &allStopWords);

void returnHeap(map <string,int> wordHash);

void cleanLine(string &line);

void makeHeap(vector<pair <string,int>> &heapWord);

void printResult(vector<pair <string,int>> heapWord);

string toLowercase(string str);

unordered_map <string,int> returnAllStopWord();

map <string,int> returnHash(unordered_map <string,int> &allStopWords);


//void printHash(map <string,int> allStopWords);

//void printStopWords(unordered_map <string,int> allStopWords);


#endif
