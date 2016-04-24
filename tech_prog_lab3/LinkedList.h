//
// Created by radiationx on 21.04.16.
//

#ifndef TECH_PROG_LAB3_LINKEDLIST_H
#define TECH_PROG_LAB3_LINKEDLIST_H

#include <iostream>

using namespace std;


template<class T>
class ListItem:T{
private:
    T data;
public:
    ListItem *nextItem;
    ListItem *prevItem;
    ListItem(){}
    T getData(){
        return data;
    }
    void setData(T element){
        data = element;
    }
};

template<class P, int size>
class Block{
public:
    ListItem<P> *items = new ListItem<P>[size];
    Block *nextBlock;
    Block *prevBlock;
    Block(){};
};

template<class T, int blockSize>
class LinkedList {

private:
    int allocSize = 16;
    int size = 0;
    int blocksNumber = 0;
    Block<T, blockSize> *array;


public:
    LinkedList(){
        array =  new Block<T, blockSize>[allocSize];
    }
    void addFirst(T element) {

    }

    void add(T element) {
        array[0].items[0].setData(element);
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
        return array[position%blockSize].items[position].getData();
    }

    int getSize() {
        return size;
    }

private:
    void reAlloc() {
        allocSize += allocSize;
        T *temp = new T[allocSize];
        for (int i = 0; i < size; i++) {
            temp[i] = array[i];
        }
        array = temp;
        delete[](temp);
    }

};


#endif //TECH_PROG_LAB3_LINKEDLIST_H
