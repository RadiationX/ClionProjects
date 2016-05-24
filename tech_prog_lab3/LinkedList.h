//
// Created by radiationx on 21.04.16.
//

#ifndef TECH_PROG_LAB3_LINKEDLIST_H
#define TECH_PROG_LAB3_LINKEDLIST_H
#define blockSize 4

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
    ListItem<T> *items;
    Block *next = NULL;
    Block *prev = NULL;

    Block() {
        items = new ListItem<T>[size];
    };

    void addItem(ListItem<T> item) {
        items[length] = item;
        if (length != size)
            length++;
    }

    void addItem(T element) {
        items[length].setData(element);
        if (length != size)
            length++;

    }


    void addItem(T element, int position) {
        items[position].setData(element);
        if (length != size)
            length++;

    }

    void addBegin(ListItem<T> item) {
        for (int i = size - 1; i > 0; i--) {
            items[i] = items[i - 1];
        }
        if (length != size)
            length++;
        items[0] = item;
    }

    void addBegin(T element) {
        for (int i = size - 1; i > 0; i--) {
            items[i] = items[i - 1];
        }
        if (length != size)
            length++;
        items[0].setData(element);
    }

    void add(ListItem<T> item, int position) {
        if(items[position].isEmpty()&&!item.isEmpty())
            length++;
        items[position] = item;


    }

    int getSize() {
        return length;
    }

    ListItem<T> get(int position) {
        return items[position];
    }
};

template<class T>
class LinkedList {
private:
    Block<T, blockSize> *firstBlock = NULL;
    Block<T, blockSize> *lastBlock = NULL;
    int listSize = 0;
    int blocksSize = 0;
public:
    LinkedList() {

    }

    void PrintData() {
        int block = 0;
        if (firstBlock == NULL)
            cout << "Список пуст.\n";
        else {
            cout << "Begin block " << firstBlock << endl;
            Block<T, blockSize> *tmp = firstBlock;
            while (tmp != NULL) {
                for (int i = 0; i < blockSize; i++) {
                    cout << "block[" << block << ", " << i << "] " << tmp->items[i].getData().key << endl;
                }
                tmp = tmp->next;
                block++;
            }
            cout << "End block " << lastBlock << endl;
        }
    };

    void addBegin(T element) {
        add(element, 0);
    }

    void add(T element) {
        add(element, listSize);
    }

    void add(T element, int position) {
        cout << "---------------" << endl;
        int currentPosition = 0;
        int needBlockPos = position / blockSize;
        int needItemPos = position % blockSize;
        Block<T, blockSize> *needBlock;
        cout<<"Block: "<<needBlockPos<<" Item: "<<needItemPos<<endl;


        if (position > listSize) {
            cout << "NE VOTKNESH!!!" << endl;
            return;
        }
        Block<T, blockSize> *currentBlock;
        if (isEmpty()) {
            currentBlock = new Block<T, blockSize>;
            firstBlock = currentBlock;
            lastBlock = currentBlock;
            currentBlock->addItem(element);
            //blocksSize++;
        } else {
            int i = 0;
            //currentBlock = firstBlock;
            needBlock = firstBlock;
            needBlock = getNeedBlock(needBlock, needBlockPos);

            //cout << "Last Length: " << lastBlock->length << endl;
            //cout << "Last BLASD% " << listSize % blockSize << endl;

            if (listSize % blockSize == 0) {
                if (lastBlock->length == blockSize) {
                    cout << "Create New Block" << endl;
                    for (int i = 0; i < 2; i++) {

                    }
                    Block<T, blockSize> *newBlock = new Block<T, blockSize>;

                    lastBlock->next = newBlock;
                    newBlock->prev = lastBlock;
                    lastBlock = newBlock;

                    cout<<"new block "<<newBlock->length<<endl;
                    cout<<"last block "<<lastBlock->length<<endl;
                    needBlock = firstBlock;
                    needBlock = getNeedBlock(needBlock, needBlockPos);
                } else {

                }

            }
            //PrintData();
            cout<<"Need Block: "<<needBlock<<"; Current Block: "<<endl;
            if(position != listSize)
                shiftItems(needBlock, needItemPos);
            /*if (needBlock->length == blockSize) {
//PrintData();



            }*/

            PrintData();

            cout<<"need block size "<<needBlock->length<<endl;
            cout<<"need block size "<<lastBlock->length<<endl;


            if (position == 0) {
                needBlock->addBegin(element);
                firstBlock = needBlock;
            } else {
                needBlock->addItem(element, needItemPos);
            }
        }
        listSize++;
        cout << "---------------" << endl<<endl;
    }

    Block<T, blockSize> *getNeedBlock(Block<T, blockSize> *needBlock, int needBlockPosition){
        for(int i = 0; i<needBlockPosition; i++){
            if(needBlock->next==NULL)
                break;
            needBlock = needBlock->next;
        }
        return needBlock;
    }
    
    bool isEmpty() {
        return firstBlock == NULL && lastBlock == NULL;
    }

    void remove(int position) {

    }

    void clear() {

    }

    //Сдвиг элементов к концу
    void shiftItems(Block<T, blockSize> *fromBlock, int fromItem) {
        Block<T, blockSize> *block = lastBlock;
        fromBlock = fromBlock==firstBlock?fromBlock:fromBlock->prev;
        while (block != fromBlock) {
            for (int i = blockSize - 1; i > -1; i--) {
                if (i == 0) {
                    if(block->prev==NULL)
                        break;
                    block->add(block->prev->items[blockSize - 1], i);
                } else {
                    block->add(block->items[i - 1], i);
                }
            }
            block = block->prev;
        }
    }

};


#endif //TECH_PROG_LAB3_LINKEDLIST_H
