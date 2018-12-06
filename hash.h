//
// Created by willworthington on 12/4/2018.
//

#ifndef CHEATERS_HASH_H
#define CHEATERS_HASH_H

#include <vector>
#include <list>
#include <string>

using namespace std;

class Hash{

private:
    static const int PRIME = 17;
    static const int ONE_MILLION = 1000000;
    static const int ONE_HUNDRED_THOUSAND = 100000;
    static const int HASH_TABLE_SIZE = ONE_HUNDRED_THOUSAND;

    vector <string> key;
    int keyLength;  // the vector "key" will be n-words long
    vector <string> fileNames;
    list<int>* hashTable[HASH_TABLE_SIZE];
    vector<vector<int>> collisionTable;



public:

    //Hash();
    Hash(int n);


    //all functions used in filling the hash table
    int hashFunction();
    unsigned int stringToInt(const string s);
    void scanFile(const string dName, const string fName, const int fileIndex);  //scans through all files in directory and hashes every n-word key
    void scanDirectory(const string dName);  //scans through entire directory, calls scanFile
    void findCollisions();  //Stores number of collisions between each pair of documents in collisionTable
    void identifyCollisions(const int bound);  //Identifies the number of collisions greater than the arbitrary threshold
    string cleanText(const string dirtyWord);
    int numberOfFiles();  //returns the number of files in current directory.  **Only call after directory has been searched



    //all functions used in reading/analyzing the hash table

};

#endif //CHEATERS_HASH_H
