//
// Created by radiationx on 21.04.16.
//

#ifndef TECH_PROG_LAB3_LINKEDLIST_H
#define TECH_PROG_LAB3_LINKEDLIST_H

#include <iostream>

using namespace std;

template<typename T>
class LinkedList {
private:
    T *lol = new T[3];
    int size = 0;
public:
    void add(T element) {
        lol[size] = element;
        size++;
    }

    T get(int position) {
        return lol[position];
    }

    int getSize() {
        return size;
    }

};


#endif //TECH_PROG_LAB3_LINKEDLIST_H
