#include "functions.hpp"
#define K 20
#define ALL 2

void makeHeap(vector<pair <string,int>> &heapWord){

    pair <string,int> father, sonRight;
    int end = heapWord.size(); 
    int size = (heapWord.size()-1)/2; 

    for(int i=size; i >= 0; i--){ 
        father = heapWord[i]; 
        int son = 2*i+1;
        while(son<end){ //acho que posso tirar o igual

            if(son < end){
                if(((son+1) < end) && (heapWord[son].second > heapWord[son+1].second)){
                    son++;
                }
            }

            if(father.second > heapWord[son].second){
                heapWord[i] = heapWord[son];
                i = son;
                son = 2*i + 1;
            }
            else{
                son = end + 1;
            }
        }
        heapWord[i] = father;
    }
}

void lookInTheHeap(pair <string,int> auxHeapWord, vector<pair <string,int>> &heapWord){

    if(auxHeapWord.second > heapWord[0].second){
        heapWord[0] = auxHeapWord;
        makeHeap(heapWord);
    }

}

void printResult(vector<pair <string,int>> heapWord){
    cout << endl << "\n\t\t  }-----------[RANK]-----------{"<< endl << endl;
    for(int j=0; j<(int)heapWord.size(); j++){
        string space = "   ", space2 = "  ";
        if(j<9){
            cout << " \t\t       "<< j+1 << "º" << space << heapWord[j].first << space << "\t" << heapWord[j].second << endl;
        }
        else{
            cout << " \t\t       "<< j+1 << "º" << space2 << heapWord[j].first << space2 << "\t" << heapWord[j].second << endl;
        }
    }
    cout << "\n\t\t  }----------------------------{" << endl;
}

void returnHeap(map <string,int> wordHash){

    int i = 0;
    vector<pair <string,int>> heapWord;
    pair <string,int> auxHeapWord;

    for(auto it = wordHash.begin(); it != wordHash.end(); it++){
        if(i > K){
            auxHeapWord.first = it->first;
            auxHeapWord.second = it->second;
            lookInTheHeap(auxHeapWord,heapWord);
        }
        else if(i == K){
            makeHeap(heapWord);
            auxHeapWord.first = it->first;
            auxHeapWord.second = it->second;
            lookInTheHeap(auxHeapWord,heapWord);
            i++;
        }
        else{
            auxHeapWord.first = it->first;
            auxHeapWord.second = it->second;
            heapWord.push_back(auxHeapWord);
            i++;

        }
    }

    printResult(heapWord);
}

unordered_map <string,int> returnAllStopWord(){

    ifstream fileStopWord;
    string line, stopWord;
    unordered_map <string,int> allStopWords;

    fileStopWord.open("input/stopWord.txt");
	if(fileStopWord.is_open()){
        while(getline(fileStopWord, line)){
            istringstream stopWordToken(line);
            while(stopWordToken >> stopWord ){
                if(!(allStopWords.find(stopWord) != allStopWords.end())){
                    allStopWords[stopWord] = 2;
                } 
            }
	    }
        
    }
    else{
        cout << "\n\t - [Error] : I'm having trouble reading the document of the StopWords ! " << endl;
    }

	fileStopWord.close();
    return allStopWords;
}

void cleanLine(string &line){
    line.erase(remove(line.begin(),line.end(),','),line.end());
    line.erase(remove(line.begin(),line.end(),'\''),line.end());
    line.erase(remove(line.begin(),line.end(),'"'),line.end());
    line.erase(remove(line.begin(),line.end(),'.'),line.end());
    line.erase(remove(line.begin(),line.end(),'!'),line.end());
    line.erase(remove(line.begin(),line.end(),'?'),line.end());
    line.erase(remove(line.begin(),line.end(),'('),line.end());
    line.erase(remove(line.begin(),line.end(),')'),line.end());    
    line.erase(remove(line.begin(),line.end(),';'),line.end());
    line.erase(remove(line.begin(),line.end(),'/'),line.end());
    line.erase(remove(line.begin(),line.end(),'\\'),line.end());
    line.erase(remove(line.begin(),line.end(),':'),line.end());
    line.erase(remove(line.begin(),line.end(),'1'),line.end());

}

string toLowercase(string word){
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    return word;
}

void updateWord(string word, map <string,int> &wordHash, unordered_map <string,int> &allStopWords ){
    
    word = toLowercase(word);

    if(allStopWords.find(word) != allStopWords.end()){
        return;
    }
    else{
        if(wordHash.find(word) != wordHash.end()){
            wordHash[word]++;
        }
        else{
            wordHash[word] = 1;
        }
    }   
}

map <string,int> returnHash(unordered_map <string,int> &allStopWords){

    ifstream file;
	string line, word, base = "input/input", pwd = "";
    map <string,int> wordHash;
   
    for(int i=0; i<ALL; i++){
        pwd = base + to_string(i) + ".txt";
        file.open(pwd);
        if(file.is_open()){
            while(getline(file, line)){
                cleanLine(line);
                istringstream wordToken(line);
                while(wordToken >> word){
                    if(word!="—"){
                        if(word.size() > 2 && word.substr(0,2) == "--"){
                            word = word.substr(2);
                            updateWord(word,wordHash,allStopWords);
                        }
                        else{
                            updateWord(word,wordHash,allStopWords);
                        }
                    }
                }

            }		
        }
        else{
            cout << "\n\t - [Error] : I'm having trouble reading the document ! " << endl;
        }

        pwd.clear();
        file.close();
    }
    
	
   // file.close();
    return wordHash;
}
