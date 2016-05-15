//
// Created by radiationx on 21.04.16.
//

#ifndef TECH_PROG_LAB3_LINKEDLIST_H
#define TECH_PROG_LAB3_LINKEDLIST_H

#include <iostream>

using namespace std;


template<class T>
class ListItem : T {
private:
    T data;
    bool empty = true;
public:
    ListItem() { }

    ListItem(T element) {
        data = element;
    }

    T getData() {
        return data;
    }

    void setData(T element) {
        data = element;
        empty = false;
    }

    bool isEmpty() {
        return empty;
    }

};

template<class T, int size>
class Block {
public:
    int length = 0;
    ListItem<T> *items = new ListItem<T>[size];
    Block *nextBlock;
    Block *prevBlock;

    Block() { };

    ListItem<T> get(int position) {
        return items[position];
    }

    Block getLast() {
        return items[length];
    }

    int getSize() {
        return length;
    }

    void add(T element, int position) {
        items[position].setData(element);
        length++;
    }
};

template<class T, int blockSize>
class LinkedList {

private:
    int allocSize = 16;
    int size = 0;
    int blocksNumber = 0;
    Block<T, blockSize> *array;


public:
    LinkedList() {
        array = new Block<T, blockSize>[allocSize];
    }

    void addBegin(T element) {
        add(element, 0);
    }

    void add(T element) {
        add(element, size);
    }

    void add(T element, int position) {

        int block = position / blockSize;
        int item = position % blockSize;
        bool needShift = (position<size||position>allocSize)&&!array[block].items[item].isEmpty();
        cout << "[begin add] to position [" << position << "] in [" << block << ", " << item << "]; size [" << size <<"]; needShift {"<<(needShift?"true":"false")<<"}";
        cout << "  ("<<position<<"<"<<size<<" || "<<position<<">"<<allocSize<<")&&"<<(!array[block].items[item].isEmpty()?"true":"false")<<endl;


        if (needShift) {
            size++;
        } else {
            if(size<=position)
                size=position+1;
        }

        if (needShift)
            shiftItems(block, item);

        array[block].add(element, item);
        cout << "[begin add] to position [" << position << "] in [" << block << ", " << item << "]; size [" << size <<"]"<<endl<<endl;
    }

    void remove(int position) {

    }

    void clear() {

    }

    void shiftItems(int fromBlock, int fromItem) {
        cout<<"call shift"<<endl;
        ListItem<T> temp, temp1;
        for (int i = size - 1, block, item; i > 0; i--) {
            block = i / blockSize;
            item = i % blockSize;
            //cout<<"shift "<<block<<" : "<<item<<endl;
            if(item<fromItem) continue;
            if (item - 1 == -1) {
                array[block].items[item] = array[block - 1].items[blockSize - 1];
            } else {
                array[block].items[item] = array[block].items[item - 1];
            }
        }
    }

    string toString() {
        string res = "";

        return res;
    }


    T get(int position) {
        return array[position % blockSize].items[position].getData();
    }

    Block<T, blockSize> getBlock(int position) {
        return array[position];
    };

    int getSize() {
        return size;
    }

    int getBlocks() {
        return blocksNumber;
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
