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
    bool empty = true;
public:
    ListItem *nextItem;
    ListItem *prevItem;
    ListItem(){}
    ListItem(T element){
        data = element;
    }
    T getData(){
        return data;
    }
    void setData(T element){
        data = element;
        empty = false;
    }
    bool isEmpty(){
        return empty;
    }

};

template<class T, int size>
class Block{
public:
    int length = 0;
    ListItem<T> *items = new ListItem<T>[size];
    Block *nextBlock;
    Block *prevBlock;
    Block(){};
    ListItem<T> get(int position){
        return items[position];
    }
    Block getLast(){
        return items[length];
    }
    int getSize(){
        return length;
    }
    void add(T element){
        items[length].setData(element);
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
    LinkedList(){
        array =  new Block<T, blockSize>[allocSize];
    }

    void addFirst(T element) {
        if(array[0].getSize()==blockSize)
            blocksNumber++;
        size++;
        if(array[0].get(0).isEmpty()){
            add(element);
        } else{
            shiftItems(0,0);
            array[0].items[0] = {element};
        }

    }

    void add(T element){
        if(array[blocksNumber].getSize()==blockSize)
            blocksNumber++;

        array[blocksNumber].add(element);
        size++;
    }

    void add(T element, int position) {
        position--;
        int block = position/blockSize;
        int item = position%blockSize;
        cout<<"kuks "<<position-size<<endl;

        if(position-size>0){
            size+=position-size;
        }
        size++;
        cout<<"add "<<block<<" : "<<item<<" : "<<position<<" : "<<size<<endl;
        shiftItems(block,item);
        array[block].items[item] = {element};
    }

    void remove(int position) {

    }

    void clear() {

    }
    void shiftItems(int fromBlock, int fromItem){
        ListItem<T> temp, temp1;
        for(int i = size-1, block, item; i>0; i--){
            block = i/blockSize;
            item = i%blockSize;
            if(item-1==-1){
                array[block].items[item] = array[block-1].items[blockSize-1];
            } else{
                array[block].items[item] = array[block].items[item-1];
            }
        }
    }

    string toString() {
        string res = "";

        return res;
    }


    T get(int position) {
        return array[position%blockSize].items[position].getData();
    }
    Block<T, blockSize> getBlock(int position){
        return array[position];
    };

    int getSize() {
        return size;
    }
    int getBlocks(){
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
