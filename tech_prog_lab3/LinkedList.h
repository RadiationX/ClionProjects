//
// Created by radiationx on 21.04.16.
//

#ifndef TECH_PROG_LAB3_LINKEDLIST_H
#define TECH_PROG_LAB3_LINKEDLIST_H

#include <iostream>

using namespace std;




template<class T, int blockSize>
class LinkedList {
    class ListItem:T{
        ListItem *nextItem;
        ListItem *prevItem;
    };
    class Block{
        ListItem items[blockSize];
        Block *nextBlock;
        Block *prevBlock;
    };
private:
    int allocSize = 16;
    int length = 0;
    int blocksNumber = 0;
    T *array = new T[allocSize];

public:
    void addFirst(T element) {
        if (length == allocSize)
            reAlloc();
    }

    void add(T element) {
        if (length == allocSize)
            reAlloc();

        array[length] = element;
        length++;
    }

    void add(T element, int position) {

    }

    void remove(int position) {

    }

    void clear() {

    }

    string toString() {
        return "";
    }


    T get(int position) {
        return array[position];
    }

    int getSize() {
        return length;
    }

private:
    void reAlloc() {
        allocSize += allocSize;
        T *temp = new T[allocSize];
        for (int i = 0; i < length; i++) {
            temp[i] = array[i];
        }
        array = temp;
        delete[](temp);
    }

};


#endif //TECH_PROG_LAB3_LINKEDLIST_H
