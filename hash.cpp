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
    //cout << "hash: " << hashAddress << endl;
    return hashAddress;
}

unsigned int Hash::stringToInt(const string s){
    unsigned int val=1;
    for (int i=0; i<s.size(); i++){
        val*=s[i];
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
    cout << "Files: ";
    list<int> ::iterator  it;
    for(it=hashTable[12660]->begin(); it!=hashTable[12660]->end(); it++){
        cout << fileNames[*it] << " ";
    }

    //Close Directory
    closedir(dir);
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
