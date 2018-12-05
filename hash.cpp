//
// Created by willworthington on 12/4/2018.
//

#include "hash.h"
#include <vector>
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
}


//all functions used in filling the hash table
int Hash::hashFunction(const vector <string> key){
    return 0;
}

void Hash::scanFiles(const string dName, const string fName){
    key.clear();
    //string fName = "abf0704";
    fileNames.push_back(fName);
    ifstream myfile(dName+"/"+fName+".txt",std::iostream::binary);

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
                if(key.size()==keyLength){

                    //only use this loop to check the key by printing to console
                    for(int i=0; i<key.size(); i++){
                        cout << key[i] << " ";
                    }

                    cout << endl;
                    key.erase(key.begin());
                }
            }
        }
    }
    myfile.close();
}

void Hash::scanDirectory(const string dName){
    //ifstream directory()
    DIR *dir;
    dir = opendir(dName.c_str());
    if(!dir){
        cout << "Directory not Found!" << endl;
    }
    else{
        cout << "Directory Found!" << endl;
    }
}

int Hash::push(const HashNode* top){
    return 0;
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
