//
// Created by willworthington on 12/4/2018.
//

#include <iostream>
#include "hash.h"

using namespace std;

int main() {
    Hash h(6);
    //h.scanFiles("sm_doc_set","abf0704");
    h.scanDirectory("sm_doc_set");

}