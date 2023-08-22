#include "functions.hpp"
#include <time.h>
#include <chrono>

int main(){
	
	clock_t startTime, endTime;
  	startTime = clock();

	map <string,int> wordHash; 
	unordered_map <string,int> allStopWords;
	allStopWords = returnAllStopWord();
	wordHash = returnHash(allStopWords);
	returnHeap(wordHash);

	endTime = clock();
  	clock_t elapsedTime = endTime - startTime;
  	double elapsedTimeMs = ((double)elapsedTime/CLOCKS_PER_SEC)*1000;
	cout << endl <<"\t    The execution time was " << elapsedTimeMs << " milliseconds" << endl << endl;

	return 0;
}