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
    const static int TABLE_SIZE = 4;
    struct TableItem {
        int index = 0;
        T *item = NULL;
    };
    TableItem *indexTable = new TableItem[TABLE_SIZE];
    int tableLength = 0;
    int tableInterval = 0;

public:
    TableItem getItem(int index) {
        return indexTable[index];
    }

    int length() {
        return tableLength;
    }

    int interval() {
        return tableInterval;
    }

    void setLength(int l) {
        tableLength = l;
    }

    void setInterval(int i) {
        tableInterval = i;
    }

    T *get(int index) {
        int tIndex = 0;
        for (; tIndex < TABLE_SIZE; tIndex++) {
            if (index <= ((tIndex > 0) ? indexTable[tIndex].index : 0)) {
                break;
            }
            if (tIndex + 1 == TABLE_SIZE)
                break;
        }
        T *item = indexTable[tIndex].item;

        if (index != indexTable[tIndex].index) {
            int border = ((indexTable[tIndex].index - indexTable[tIndex - 1].index) / 2) +
                         indexTable[tIndex - 1].index;
            if (border < index) {
                tIndex--;
            }
            item = indexTable[tIndex].item;
            int i = indexTable[tIndex].index;
            while (i != index) {
                if (indexTable[tIndex].index < index) {
                    item = item->getNext();
                    i++;
                } else {
                    item = item->getPrev();
                    i--;
                }
            }
        }

        cout << "ITEM BY TABLE " << index << " : " << item->getData() << endl;
        return item;
    }

    void update(T *newItem, int index, int listLength) {
        int tIndex = 0;
        if (listLength <= TABLE_SIZE) {
            tableLength = listLength;
            bool moved = false;
            for (int j = tableLength - 1; j > index; j--) {
                indexTable[j].item = indexTable[j - 1].item;
                indexTable[j].index = indexTable[j - 1].index;
                indexTable[j].index++;
                moved = true;
            }
            tIndex = index;
            if (!moved) {
                indexTable[tIndex].index = tIndex;
            }
            indexTable[tIndex].item = newItem;
        } else {
            for (; tIndex < tableLength; tIndex++) {
                if (index <= ((tIndex > 0) ? indexTable[tIndex].index : 0))
                    break;
                if (tIndex + 1 == tableLength)
                    break;
            }

            for (int j = tIndex == 0 ? tIndex + 1 : tIndex; j < tableLength; j++)
                indexTable[j].index++;

            if (indexTable[tIndex].index <= index)
                indexTable[tIndex].index = index;
            indexTable[tIndex].item = newItem;

            //Array uniformity
            if (((listLength - tableLength) % (tableLength - 1) == 0)) {
                tableInterval = (listLength - tableLength) / (tableLength - 1);
                cout << "NEW TABLE INTERVAL: " << tableInterval << endl;
                for (int j = 1; j < TABLE_SIZE - 1; j++) {
                    int newIndex = j + j * tableInterval;
                    indexTable[j].item = get(newIndex);
                    indexTable[j].index = newIndex;
                }
            }
        }
        cout << "INFO " << listLength << " : " << tableLength << " : " << index << " : " << tIndex << endl;
        cout << endl;
    }
};

template<typename T>
class LinkedList {
private:
    LinkedItem<T> *head = NULL;
    LinkedItem<T> *tail = NULL;
    int length = 0;
    IndexTable<LinkedItem<T>> indexTable;

public:
    void addHead(T data) {
        add(data, 0);
    }

    void addTail(T data) {
        add(data, length);
    }


    void add(T data, int index) {
        //cout << "add " << data << " to " << index << endl;
        LinkedItem<T> *newItem = new LinkedItem<T>();
        newItem->setData(data);
        if (index > length)
            index = length;
        if (index < 0)
            index = 0;

        if (length == 0) {
            //Create first element
            head = newItem;
            tail = newItem;
        } else if (index == 0) {
            //Add to head
            newItem->setNext(head);
            head->setPrev(newItem);
            head = newItem;
        } else if (index == length) {
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
        length++;
        cout << "NEW ITEM " << newItem->getData() << endl;
        indexTable.update(newItem, index, length);
    }

    LinkedItem<T> *getItem(int index) {
        if (index < 0 || index >= length)
            return NULL;
        return indexTable.get(index);
    }

    T get(int index) {
        return getItem(index)->getData();
    }

    void remove(int index) {
        if (index < 0 || index >= length)
            return;
        LinkedItem<T> *item = NULL;
        if (index == 0) {
            item = head;
        } else if (index == length - 1) {
            item = tail;
        } else {
            item = getItem(index);
        }
        remove(item);
    }

    void remove(LinkedItem<T> *item) {
        cout << item->getData() << " : " << head->getData() << " : " << tail->getData() << endl;
        if (length == 1) {
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
        length--;
        /*if (length <= TABLE_SIZE) {
            indexTable.setLength(length);
            indexTable[indexTable.length(] - 1).index = 0;
            indexTable[indexTable.length(] - 1).item = NULL;
        }*/
        //cout << "TABLE LENGTH " << indexTable.length() << ", LENGTH " << length << endl;
    }

    void clear() {
        if (length < 1) return;
        int length = this->length;
        for (int i = 0; i < length; i++) {
            remove(this->length - 1);
        }
    }

    void printTable() {
        for (int i = 0; i < indexTable.length(); i++) {
            cout << "TABLE ITEM[" << i << "]: " << indexTable.getItem(i).index << " : "
                 << indexTable.getItem(i).item->getData()
                 << endl;
        }
    }

    void print() {
        if (length > 0) {
            int i = 0;
            LinkedItem<T> *temp = head;
            cout << endl;
            cout << "HEAD ITEM: " << head->getData() << endl;
            while (temp != NULL) {
                cout << "[" << i << "] " << temp->getData() << endl;
                temp = temp->getNext();
                i++;
            }
            cout << "TAIL ITEM: " << tail->getData() << endl;
        }

        cout << "SIZE " << size() << endl;
        cout << endl;
    }

    int size() {
        return length;
    }
};

#endif //CLIONPROJECTS_LINKEDLIST_H
