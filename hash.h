//
// Created by willworthington on 12/4/2018.
//

#ifndef CHEATERS_HASH_H
#define CHEATERS_HASH_H

#include <vector>
#include <string>

using namespace std;

class Hash{

private:
    static const int HASH_TABLE_SIZE = 103;

    vector <string> key;
    int keyLength;  // the vector "key" will be n-words long
    vector <string> fileNames;

    struct HashNode{
        int index;
        HashNode *next;
    };  //node contains an index of a file in "fileName" vector and a pointer to next node

    HashNode* hashTable[HASH_TABLE_SIZE];  // an array of pointers to hashNodes

public:

    //Hash();
    Hash(int n);


    //all functions used in filling the hash table
    int hashFunction(const vector <string> key);
    void scanFiles(const string dName, const string fName);  //scans through all files in directory and hashes every n-word key
    void scanDirectory(const string dName);  //scans through entire directory, calls scanFile
    int push(const HashNode* top);  // pushes new node to top of linked list for its row
    string cleanText(const string dirtyWord);


    //all functions used in reading/analyzing the hash table

};

#endif //CHEATERS_HASH_H
