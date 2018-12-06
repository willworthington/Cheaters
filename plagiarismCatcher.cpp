//
// Created by willworthington on 12/4/2018.
//

#include <iostream>
#include "hash.h"

using namespace std;

int main() {

    //Hard coded for clion testing
    int sequenceSize = 6;
    int threshold = 200;
    string directory = "sm_doc_set";


    Hash h(sequenceSize);
    h.scanDirectory(directory);

    cout << "NOTABLY SIMILAR FILES" << endl;
    h.findCollisions();
    h.identifyCollisions(threshold);

}