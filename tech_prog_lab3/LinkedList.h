//
// Created by radiationx on 21.04.16.
//

#ifndef TECH_PROG_LAB3_LINKEDLIST_H
#define TECH_PROG_LAB3_LINKEDLIST_H
#define blockSize 4

#include <iostream>

using namespace std;


template<class T>
class ListItem {
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


    void addItem(T element, int index) {
        items[index].setData(element);
        if (length != size)
            length++;

    }

    void addBegin(T element) {
        for (int i = size - 1; i > 0; i--) {
            items[i] = items[i - 1];
        }
        if (length != size)
            length++;
        items[0].setData(element);
    }

    void move(ListItem<T> item, int index) {
        if (items[index].isEmpty() && !item.isEmpty())
            length++;
        items[index] = item;
    }

    int getSize() {
        return length;
    }

    bool isEmpty() {
        if (length == 0)
            return true;

        for (int i = 0; i < size; i++)
            if (!items[i].isEmpty())
                return false;

        return true;
    }


    void remove(int index) {
        ListItem<T> suka;
        items[index] = suka;
    }
};

template<class T>
class LinkedList {
private:
    Block<T, blockSize> *firstBlock = NULL;
    Block<T, blockSize> *lastBlock = NULL;
    int listSize = 0;
    int blocksNumber = 0;
public:
    LinkedList() {

    }

    void addBegin(T element) {
        add(element, 0);
    }

    void add(T element) {
        add(element, listSize);
    }

    void add(T element, int index) {
        int currentIndex = 0;
        int needBlockPos = index / blockSize;
        int needItemPos = index % blockSize;
        Block<T, blockSize> *needBlock;

        if (indexOutOfRange(index))
            return;

        if (isEmpty()) {
            Block<T, blockSize> *newBlock = new Block<T, blockSize>;
            blocksNumber++;
            firstBlock = newBlock;
            lastBlock = newBlock;
            newBlock->addItem(element, newBlock->length);
        } else {
            needBlock = getNeedBlock(firstBlock, needBlockPos);
            if (listSize % blockSize == 0) {
                if (lastBlock->length == blockSize) {
                    Block<T, blockSize> *newBlock = new Block<T, blockSize>;
                    blocksNumber++;

                    lastBlock->next = newBlock;
                    newBlock->prev = lastBlock;
                    lastBlock = newBlock;

                    needBlock = getNeedBlock(firstBlock, needBlockPos);
                }
            }
            if (index != listSize)
                shiftItemsToEnd(needBlock, needItemPos);

            if (index == 0) {
                needBlock->addBegin(element);
                firstBlock = needBlock;
            } else {
                needBlock->addItem(element, needItemPos);
            }
        }
        listSize++;
    }

    bool isEmpty() {
        return firstBlock == NULL && lastBlock == NULL;
    }

    void remove(int index) {
        if (indexOutOfRange(index))
            return;
        getNeedBlock(firstBlock, index / blockSize)->remove(index % blockSize);
        shiftItemsToStart(getNeedBlock(firstBlock, index / blockSize), index % blockSize);
        cout << "EBAL V ROT RABOTAET " << lastBlock->isEmpty() << endl;
        if (lastBlock->isEmpty()) {
            lastBlock->prev->next = NULL;
            Block<T, blockSize> *prev = lastBlock->prev;
            delete (lastBlock->prev);
            lastBlock = prev;
        }
        listSize--;
    }

    void clear() {

    }

    int size() {
        return listSize;
    }

    T get(int index) {
        if (indexOutOfRange(index)) {
            cout << "RETURN NEW EMPTY ELEMENT" << endl;
            T empty;
            return empty;
        } else
            return getNeedBlock(firstBlock, index / blockSize)->items[index % blockSize].getData();
    }


    //only for my item class
    void printData() {
        int block = 0;
        if (firstBlock == NULL)
            cout << "Список пуст.\n";
        else {
            cout << "Begin block " << firstBlock << endl;
            Block<T, blockSize> *tmp = firstBlock;
            int count = 0;
            while (tmp != NULL) {
                for (int i = 0; i < blockSize; i++) {
                    cout << count << "\t'" << tmp << "'-[" << block << ", " << i << "] " <<
                    tmp->items[i].getData().key << endl;
                    count++;
                }
                tmp = tmp->next;
                block++;
            }
            cout << "End block " << lastBlock << endl;
        }
    }

    void printHex() {

        if (isEmpty())
            cout << "Список пуст.\n";
        else {
            int block = 0;
            cout << "Begin block " << firstBlock << endl;
            Block<T, blockSize> *tmp = firstBlock;
            while (tmp != NULL) {
                cout << "Block hex [" << tmp << "]" << endl;
                for (int i = 0; i < blockSize; i++) {
                    cout << "   Block[" << block << ", " << i << "] Item hex: [" << &tmp->items[i] << "] " <<
                    (tmp->items[i].isEmpty() ? "empty" : "") << endl;
                }
                cout << endl;
                tmp = tmp->next;
                block++;
            }
            cout << "End block " << lastBlock << endl;
        }
    }


private:
    bool indexOutOfRange(int index) {
        if (index < 0 || index > listSize) {
            cout << "INDEX [" << index << "] OUT OF RANGE" << endl;
            return true;
        }
        return false;
    }

    Block<T, blockSize> *getNeedBlock(Block<T, blockSize> *needBlock, int needBlockIndex) {
        for (int i = 0; i < needBlockIndex; i++) {
            if (needBlock->next == NULL)
                break;
            needBlock = needBlock->next;
        }
        return needBlock;
    }

    //Сдвиг элементов к концу
    void shiftItemsToEnd(Block<T, blockSize> *fromBlock, int fromItem) {
        Block<T, blockSize> *block = lastBlock;
        fromBlock = fromBlock == firstBlock ? fromBlock : fromBlock->prev;
        while (block != fromBlock) {
            for (int i = blockSize - 1; i > -1; i--) {
                if (i == 0) {
                    if (block->prev == NULL)
                        break;
                    block->move(block->prev->items[blockSize - 1], i);
                } else {
                    block->move(block->items[i - 1], i);
                }
            }
            block = block->prev;
        }
    }

    void shiftItemsToStart(Block<T, blockSize> *toBlock, int fromItem) {
        Block<T, blockSize> *block = toBlock;
        while (block != NULL) {
            for (int i = 0; i < blockSize; i++) {
                if (toBlock == block && i < fromItem)
                    continue;
                if (i == blockSize - 1) {
                    if (block->next == NULL)
                        break;
                    block->move(block->next->items[0], i);
                } else {
                    block->move(block->items[i + 1], i);
                }
            }
            block = block->next;
        }
    }
};


#endif //TECH_PROG_LAB3_LINKEDLIST_H
