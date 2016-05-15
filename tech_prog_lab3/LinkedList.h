//
// Created by radiationx on 21.04.16.
//

#ifndef TECH_PROG_LAB3_LINKEDLIST_H
#define TECH_PROG_LAB3_LINKEDLIST_H

#include <iostream>

using namespace std;


template<class T>
class ListItem : T {





};

template<class T, int size>
class Block {
public:
    Block *nextBlock;
    Block *prevBlock;
};

template<class T, int blockSize>
class LinkedList {



public:
    LinkedList() {

    }

    void addBegin(T element) {

    }

    void add(T element) {

    }

    void add(T element, int position) {

    }

    void remove(int position) {

    }

    void clear() {

    }

    void shiftItems(int fromBlock, int fromItem) {

    }
};


#endif //TECH_PROG_LAB3_LINKEDLIST_H
