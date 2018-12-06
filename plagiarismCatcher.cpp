//
// Created by willworthington on 12/4/2018.
//

#include <iostream>
#include "hash.h"

using namespace std;

int main() {
    Hash h(6);
    //h.scanFile("sm_doc_set","abf0704.txt",0);
    //cout << endl << endl << "Break" << endl << endl;
    //h.scanFile("sm_doc_set","abf70402.txt",0);

    h.scanDirectory("sm_doc_set");
    //h.hashFunction();

}