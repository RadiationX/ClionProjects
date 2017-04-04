//
// Created by radiationx on 09.03.17.
//

#ifndef CLIONPROJECTS_LINKEDLIST_H
#define CLIONPROJECTS_LINKEDLIST_H

#include <iostream>

using namespace std;

template<typename T>
class LinkedItem {
private:
    LinkedItem<T> *prev = NULL;
    LinkedItem<T> *next = NULL;
    T data;
public:
    LinkedItem *getPrev() {
        return prev;
    }

    void setPrev(LinkedItem *prev) {
        LinkedItem::prev = prev;
    }

    LinkedItem *getNext() {
        return next;
    }

    void setNext(LinkedItem *next) {
        LinkedItem::next = next;
    }

    T getData() {
        return data;
    }

    void setData(T data) {
        LinkedItem::data = data;
    }
};

template<typename T>
class IndexTable {
private:
    const static int TABLE_SIZE = 6;
    struct TableItem {
        int index = 0;
        LinkedItem<T> *item = NULL;
    };
    TableItem *table = new TableItem[TABLE_SIZE];
    int tableLength = 0;
    int tableInterval = 0;

    int getTableIndex(int listIndex) {
        int tableIndex = 0;
        int delta = table[tableLength - 1].index;
        for (int i = 0; i < tableLength; i++) {
            if (abs(listIndex - table[i].index) < delta) {
                tableIndex = i;
                delta = abs(listIndex - table[i].index);
            }
        }
        return tableIndex;
    }

    void restoreUniformity(int listLength) {
        if (((listLength - tableLength) % (tableLength - 1) == 0)) {
            tableInterval = (listLength - tableLength) / (tableLength - 1);
            for (int j = 1; j < tableLength - 1; j++) {
                int newIndex = j + j * tableInterval;
                table[j].item = get(newIndex);
                table[j].index = newIndex;
            }
        }
    }

public:
    int length() {
        return tableLength;
    }

    int interval() {
        return tableInterval;
    }

    TableItem getItem(int index) {
        return table[index];
    }

    LinkedItem<T> *get(int listIndex) {
        int tIndex = getTableIndex(listIndex);
        LinkedItem<T> *item = table[tIndex].item;
        int i = table[tIndex].index;
        while (i != listIndex) {
            if (table[tIndex].index < listIndex) {
                item = item->getNext();
                i++;
            } else {
                item = item->getPrev();
                i--;
            }
        }
        return item;
    }

    void add(LinkedItem<T> *newItem, int listIndex, int listLength) {
        int tIndex = listIndex;
        if (listLength <= TABLE_SIZE) {
            bool moved = false;
            for (int j = tableLength; j > tIndex; j--) {
                table[j].item = table[j - 1].item;
                table[j].index = table[j - 1].index;
                table[j].index++;
                moved = true;
            }
            if (!moved) {
                table[tIndex].index = tIndex;
            }
            table[tIndex].item = newItem;
            tableLength++;
        } else {
            tIndex = getTableIndex(listIndex);

            for (int i = tIndex == 0 ? tIndex + 1 : tIndex; i < tableLength; i++) {
                table[i].index++;
            }

            if (table[tIndex].index <= listIndex) {
                table[tIndex].index = listIndex;
            }

            table[tIndex].item = newItem;

            restoreUniformity(listLength);
        }
    }

    void remove(int listIndex, int listLength) {
        int tIndex = listIndex;
        if (listLength < TABLE_SIZE) {
            for (int j = tIndex; j < tableLength - 1; j++) {
                table[j].item = table[j + 1].item;
                table[j].index = table[j + 1].index;
                table[j].index--;
                if (tableLength - 1 == j + 1) {
                    table[j + 1].item = NULL;
                    table[j + 1].index = 0;
                }
            }
            tableLength--;
        } else {
            tIndex = getTableIndex(listIndex);

            bool shiftToRight = false;
            for (int i = tIndex; i < tableLength - 1; i++) {
                if (table[i].index + 1 == table[i + 1].index || table[i].index <= listIndex) {
                    shiftToRight = true;
                    break;
                }
            }
            if (shiftToRight) {
                table[tIndex].item = get(table[tIndex].index + 1);
                table[tIndex].index++;
                for (int i = tIndex; i < tableLength; i++) {
                    if (i + 1 < tableLength) {
                        int cur = table[i].index;
                        int next = table[i + 1].index;
                        if (cur == next) {
                            table[i + 1].item = get(table[i + 1].index + 1);
                            table[i + 1].index++;
                        }
                    }
                    table[i].index--;
                }
            } else {
                table[tIndex].item = get(table[tIndex].index - 1);
                table[tIndex].index--;
                for (int i = tIndex; i > 0; i--) {
                    if (i - 1 > 0) {
                        int cur = table[i].index;
                        int next = table[i - 1].index;
                        if (cur == next) {
                            table[i - 1].item = get(table[i - 1].index - 1);
                            table[i - 1].index--;
                        }
                    }
                }
            }
            restoreUniformity(listLength);
        }
    }
};

template<typename T>
class LinkedList {
private:
    LinkedItem<T> *head = NULL;
    LinkedItem<T> *tail = NULL;
    int listLength = 0;
    IndexTable<T> indexTable;

    LinkedItem<T> *getItem(int index) {
        if (index < 0 || index >= listLength)
            return NULL;
        return indexTable.get(index);
    }

    void remove(LinkedItem<T> *item) {
        if (listLength == 1) {
            //Delete first element
            head = NULL;
            tail = NULL;
        } else if (item == head) {
            //Remove from head
            head = item->getNext();
            head->setPrev(NULL);
            item->setNext(NULL);
        } else if (item == tail) {
            //Remove from tail
            tail = item->getPrev();
            tail->setNext(NULL);
            item->setPrev(NULL);
        } else {
            //Remove from position
            item->getPrev()->setNext(item->getNext());
            item->getNext()->setPrev(item->getPrev());
            item->setPrev(NULL);
            item->setNext(NULL);
        }
        delete (item);
        listLength--;
    }

    bool checkBounds(int index) {
        bool res = index < 0 || index >= listLength;
        if (res) {
            cout << "Error: Index out of bounds [index: " << index << ", length: " << listLength << "]" << endl;
        }
        return res;
    }

public:
    int length() {
        return listLength;
    }

    void addHead(T data) {
        add(data, 0);
    }

    void addTail(T data) {
        add(data, listLength);
    }

    void add(T data, int index) {
        if (index != listLength && checkBounds(index))
            return;
        LinkedItem<T> *newItem = new LinkedItem<T>();
        newItem->setData(data);
        if (listLength == 0) {
            //Create first element
            head = newItem;
            tail = newItem;
        } else if (index == 0) {
            //Add to head
            newItem->setNext(head);
            head->setPrev(newItem);
            head = newItem;
        } else if (index == listLength) {
            //Add to tail
            newItem->setPrev(tail);
            tail->setNext(newItem);
            tail = newItem;
        } else {
            //Add to position
            LinkedItem<T> *target = getItem(index);
            target->getPrev()->setNext(newItem);
            newItem->setPrev(target->getPrev());
            target->setPrev(newItem);
            newItem->setNext(target);
        }
        listLength++;
        indexTable.add(newItem, index, listLength);
    }


    T get(int index) {
        if (checkBounds(index))
            return NULL;
        return getItem(index)->getData();
    }

    void remove(int index) {
        if (checkBounds(index))
            return;
        LinkedItem<T> *item = NULL;
        if (index == 0) {
            item = head;
        } else if (index == listLength - 1) {
            item = tail;
        } else {
            item = getItem(index);
        }
        indexTable.remove(index, listLength - 1);
        remove(item);
    }


    void clear() {
        if (listLength < 1) return;
        int length = this->listLength;
        for (int i = 0; i < length; i++) {
            remove(this->listLength - 1);
        }
    }

    IndexTable<T> getIndexTable() {
        return indexTable;
    }

    LinkedItem<T> *getLinkedHead() {
        return head;
    }

    LinkedItem<T> *getLinkedTail() {
        return tail;
    }
};

#endif //CLIONPROJECTS_LINKEDLIST_H
