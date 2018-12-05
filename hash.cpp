//
// Created by willworthington on 12/4/2018.
//

#include "hash.h"
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

Hash::Hash(int n){
    keyLength=n;
}


//all functions used in filling the hash table
int Hash::hashFunction(const vector <string> key){
    return 0;
}

void Hash::scanFiles(const string dName){
    //string myfile;
    string fileName = "abf0704";
    ifstream myfile(dName+"/"+fileName+".txt",std::iostream::binary);

    if(myfile){
        //cout << "File Valid!" << endl;
        int count=0;
        string text;
        while(!myfile.eof()){
            myfile >> text;
            //key.push_back(text);
            //text = cleanText(text);
            cout << text << " ";
            //count++;
        }
        //cout << key[0] << endl;

    }


}

void Hash::scanDirectory(const string dName){

}

int Hash::push(const HashNode* top){
    return 0;
}

string Hash::cleanText(const string dirtyWord){
    string cleanWord;
    cleanWord += "A";


    return cleanWord;
}
