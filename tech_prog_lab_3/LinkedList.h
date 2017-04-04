#ifndef TECH_PROG_LAB_3_LINKEDLIST_H
#define TECH_PROG_LAB_3_LINKEDLIST_H
#define blockSize 10

#include <iostream>

using namespace std;


template<class T>
class ListItem {
private:
    T data;
    bool empty = true;
public:
    ListItem() { }

    ListItem(T item) {
        data = item;
    }

    T getData() {
        return data;
    }

    void setData(T item) {
        data = item;
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

    void addItem(T item, int index) {
        items[index].setData(item);
        if (length != size)
            length++;
    }

    void move(ListItem<T> item, int index) {
        if (items[index].isEmpty() && !item.isEmpty() && size > length)
            length++;
        items[index] = item;
    }

    int getSize() {
        return length;
    }

    bool isEmpty() {
        if (length > 0)
            return false;

        for (int i = 0; i < size; i++)
            if (!items[i].isEmpty())
                return false;

        return true;
    }

    void remove(int index) {
        ListItem<T> temp;
        items[index] = temp;
        length--;
    }
};

template<class T>
class LinkedList {
private:
    Block<T, blockSize> *firstBlock = NULL;
    Block<T, blockSize> *lastBlock = NULL;
    int listSize = 0;
    int blocksNumber = 0;

    Block<T, blockSize> *lastBlockSeq = NULL;
    int lastItemIndexSeq = 0;
public:
    LinkedList() { }

    ~LinkedList() { }

    void addBegin(T item) {
        add(item, 0);
    }

    void add(T item) {
        add(item, listSize);
    }

    void add(T item, int index) {
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
            newBlock->addItem(item, newBlock->getSize());
        } else {
            needBlock = getNeedBlock(firstBlock, needBlockPos);
            if (listSize % blockSize == 0) {
                if (lastBlock->getSize() >= blockSize) {
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

            if (index == listSize)
                needBlock = lastBlock;

            needBlock->addItem(item, needItemPos);
        }
        listSize++;
    }

    bool isEmpty() {
        return firstBlock == NULL && lastBlock == NULL;
    }

    void remove(int index) {
        if (indexOutOfRange(index)||index==listSize)
            return;

        Block<T, blockSize> *needBlock = getNeedBlock(firstBlock, index / blockSize);
        needBlock->remove(index % blockSize);
        if(index%blockSize!=needBlock->getSize())
            shiftItemsToStart(needBlock, index % blockSize);
        //lastBlock->length--;
        if (lastBlock->isEmpty()) {
            Block<T, blockSize> *prev = lastBlock->prev;
            delete (lastBlock);
            lastBlock = prev;
            lastBlock->next = NULL;
            blocksNumber--;
        }
        listSize--;
    }

    void clear() {
        if (isEmpty()) {
            cout << "List already empty" << endl;
            return;
        }
        Block<T, blockSize> *block = firstBlock;
        while (block != NULL) {
            delete[](block->items);
            delete (block);
            block = block->next;
        }
        firstBlock = NULL;
        lastBlock = NULL;
        listSize = 0;
        blocksNumber = 0;
    }

    int size() {
        return listSize;
    }

    int blocks() {
        return blocksNumber;
    }

    int getBlockSize() {
        return blockSize;
    }

    T get(int index) {
        if (indexOutOfRange(index)) {
            cout << "RETURN NEW EMPTY ELEMENT" << endl;
            T empty;
            return empty;
        }
        return getNeedBlock(firstBlock, index / blockSize)->items[index % blockSize].getData();
    }

    void set(T item, int index) {
        if (indexOutOfRange(index))
            return;
        getNeedBlock(firstBlock, index / blockSize)->items[index % blockSize].setData(item);
    }

    //Sequential access
    void startSeqAccess() {
        lastBlockSeq = firstBlock;
        lastItemIndexSeq = 0;
    }

    bool get(T &item) {
        return get(item, false);
    }

    bool get(T &item, bool printBlock) {

        if (isEmpty()) {
            cout << "List is empty" << endl;
            return false;
        }
        if (lastItemIndexSeq > lastBlockSeq->getSize() - 1) {
            if (lastBlockSeq->next == NULL)
                return false;
            lastBlockSeq = lastBlockSeq->next;
            lastItemIndexSeq = 0;
        }
        if (printBlock) {
            if (lastItemIndexSeq == 0) {
                cout << "Block '" << lastBlockSeq << "' size " << lastBlockSeq->getSize() << "\t";
            } else {
                cout << "\t\t\t\t\t\t";
            }
        }

        item = lastBlockSeq->items[lastItemIndexSeq].getData();
        lastItemIndexSeq++;
        return true;
    }

    void stopSeqAccess() {
        lastBlockSeq = NULL;
        lastItemIndexSeq = 0;
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
        while (block != fromBlock->prev) {
            for (int i = blockSize - 1; i >= 0; i--) {
                if (fromBlock == block && i < fromItem)
                    continue;
                if (i == 0) {
                    if (block->prev == NULL) {
                        block->length--;
                        break;
                    }
                    block->move(block->prev->items[blockSize - 1], i);
                } else {
                    block->move(block->items[i - 1], i);
                }
            }
            block = block->prev;
        }
    }

    //Сдвиг элементов к началу
    void shiftItemsToStart(Block<T, blockSize> *toBlock, int fromItem) {
        Block<T, blockSize> *block = toBlock;
        while (block != NULL) {
            for (int i = 0; i < blockSize; i++) {
                if (toBlock == block && i < fromItem)
                    continue;
                if (i == blockSize - 1) {
                    if (block->next == NULL) {
                        block->length--;
                        break;
                    }
                    block->move(block->next->items[0], i);
                } else {
                    block->move(block->items[i + 1], i);
                }
            }
            block = block->next;
        }
    }
};


#endif //TECH_PROG_LAB_3_LINKEDLIST_H
