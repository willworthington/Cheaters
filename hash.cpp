//
// Created by willworthington on 12/4/2018.
//

#include "hash.h"
#include <vector>
#include <list>
#include <iterator>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include "dirent.h"
//#includ <dirent.h>

using namespace std;

Hash::Hash(int n){
    keyLength=n;
    for(int i=0; i<HASH_TABLE_SIZE; i++){
        hashTable[i] = new list<int>;
    }
}


//all functions used in filling the hash table
int Hash::hashFunction(){

    unsigned int hashAddress=0;
    int dif;
    int mult=1;

    for(int i=0; i<key.size(); i++){
        dif = keyLength - i;
        if (i>0){
            mult*=PRIME;
        }
        hashAddress += stringToInt(key[i])*dif*mult;
    }
    hashAddress = hashAddress%HASH_TABLE_SIZE;
    return hashAddress;
}

unsigned int Hash::stringToInt(const string s){
    unsigned int val=1;
    for (int i=0; i<s.size(); i++){
        val+=s[i];
    }
    return val;
}

void Hash::scanFile(const string dName, const string fName, const int fileIndex){
    key.clear();
    ifstream myfile(dName+"/"+fName,std::iostream::binary);
    int tableIndex;

    if(myfile){
        string text;
        while(!myfile.eof()){
            myfile >> text;

            //this seems redundant with the while loop condition, but
            //it corrects the issue I was having with the last word being
            //read twice before eof() was true
            if (!myfile.eof()){
                text = cleanText(text);
                if (text.size()>0) key.push_back(text);
                if(key.size()>keyLength){
                    key.erase(key.begin());
                }
                if(key.size()==keyLength){
                    tableIndex = hashFunction();
                    hashTable[tableIndex]->push_front(fileIndex);
                }

            }
        }
    }
    myfile.close();
}

void Hash::scanDirectory(const string dName){

    //Open Directory
    DIR *dir;
    struct dirent *entry;
    dir = opendir(dName.c_str());
    int count=0;

    //Read files from directory
    if(dir){
        while ((entry=readdir(dir))){
            string fName = string(entry->d_name);
            if ((fName!=".")&&(fName!="..")){
                fileNames.push_back(fName);
                scanFile(dName,fName,count);

                count++;
            }
        }
    }
    else{
        cout << "Directory not Found!" << endl;
    }

    //Close Directory
    closedir(dir);
}

void Hash::findCollisions(){

    //initializes collisionTable to null grid of size (numberOfFiles)x(numberOfFiles)
    collisionTable.resize(sizeof(int)*numberOfFiles());
    for(int i=0; i<numberOfFiles(); i++){
        collisionTable[i].resize(sizeof(int)*numberOfFiles(),0);
    }

    int a, b;
    for(int i=0; i<HASH_TABLE_SIZE; i++){

        list<int> ::iterator it;
        for(it=hashTable[i]->begin(); it!=hashTable[i]->end(); it++){
            a=*it;
            list<int> ::iterator it2;
            for(it2=next(it); it2!=hashTable[i]->end(); it2++){
                b=*it2;
                if (a>b){
                    collisionTable[a][b]++;
                }
                else if (a<b){
                    collisionTable[b][a]++;
                }

            }
        }
    }
}

void Hash::identifyCollisions(const int bound){
    struct collisionNode{
        int value;
        int col;
        int row;
    };
    vector<collisionNode> collisionList;

    int collisions;
    for(int i=1; i<numberOfFiles(); i++){
        for(int j=0; j<i; j++){
            collisions=collisionTable[i][j];
            if(collisions>bound){
                collisionNode a {collisions, j, i};
                collisionList.push_back(a);

                //cout << a.value << " collisions: " << fileNames[a.col] << " & " << fileNames[a.row] << endl;

                //a.value = collisions;
                //a.col = j;
                //a.row = i;
                //cout << collisions << " collisions: " << fileNames[j] << " & " << fileNames[i] << endl;
            }
        }
    }

    //sort the list of collisions
    int minIndex;
    for(int i=0; i<collisionList.size()-1; i++){
        minIndex=i;
        for(int j=i+1; j<collisionList.size(); j++){
            if(collisionList[j].value<collisionList[minIndex].value){
                minIndex=j;
            }
        }
        if(i!=minIndex) {
            collisionNode temp = collisionList[minIndex];
            collisionList[minIndex] = collisionList[i];
            collisionList[i] = temp;
        }
    }

    //Print the now sorted list
    for(int i=collisionList.size()-1; i>=0; i--){
        cout << collisionList[i].value << " collisions: " << fileNames[collisionList[i].col] << " & " << fileNames[collisionList[i].row] << endl;
        //cout << a.value << " collisions: " << fileNames[a.col] << " & " << fileNames[a.row] << endl;
    }



}

string Hash::cleanText(const string dirtyWord){
    string cleanWord;
    char letter;
    bool upperCase;
    bool lowerCase;
    bool number;
    for(int i=0; i<dirtyWord.size(); i++){

        letter = dirtyWord[i];
        upperCase=(letter>='A')&&(letter<='Z');
        lowerCase=(letter>='a')&&(letter<='z');
        number=(letter>='0')&&(letter<='9');

        if(upperCase||lowerCase||number){
            if(upperCase){
                letter+=32;
            }
            cleanWord += letter;
        }
    }

    return cleanWord;
}

int Hash::numberOfFiles(){
    return fileNames.size();
}
