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
class LinkedList {
private:
    const static int TABLE_SIZE = 4;
    struct TableItem {
        int index;
        LinkedItem<T> *item;
    };
    LinkedItem<T> *head = NULL;
    LinkedItem<T> *tail = NULL;
    TableItem *indexTable = new TableItem[TABLE_SIZE];
    int length = 0;
    int tableLength = 0;
    int tableInterval = 1;

public:
    void addHead(T data) {
        add(data, 0);
    }

    void addTail(T data) {
        add(data, length);
    }

    LinkedItem<T> *getByTable(int index) {
        int tIndex = 0;
        for (; tIndex < TABLE_SIZE; tIndex++) {
            if (index <= ((tIndex > 0) ? indexTable[tIndex].index : 0)) {
                break;
            }
            if (tIndex + 1 == TABLE_SIZE)
                break;
        }
        LinkedItem<T> *item = indexTable[tIndex].item;

        if (index != indexTable[tIndex].index) {
            int border = ((indexTable[tIndex].index - indexTable[tIndex - 1].index) / 2) + indexTable[tIndex - 1].index;
            if (border <= index) {
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
        int tIndex = 0;
        if (length <= TABLE_SIZE) {
            tableLength = length;
            tIndex = tableLength - 1;
            indexTable[tIndex].index = tIndex;
            indexTable[tIndex].item = newItem;
        } else {
            for (; tIndex < TABLE_SIZE; tIndex++) {
                if (index <= ((tIndex > 0) ? indexTable[tIndex].index : 0)) {
                    break;
                }
                if (tIndex + 1 == TABLE_SIZE)
                    break;
            }

            for (int j = tIndex; j < TABLE_SIZE; j++) {
                indexTable[j].index++;
            }
            if (indexTable[tIndex].index <= index) {
                indexTable[tIndex].index = index;
                indexTable[tIndex].item = newItem;
            }

            //Array uniformity
            if (((length - TABLE_SIZE) % (TABLE_SIZE - 1) == 0)) {
                tableInterval = (length - TABLE_SIZE) / (TABLE_SIZE - 1);
                cout << "NEW TABLE INTERVAL: " << tableInterval << endl;
                for (int j = 1; j < TABLE_SIZE - 1; j++) {
                    indexTable[j].index = j + j * tableInterval;
                    indexTable[j].item = getItem(indexTable[j].index);
                }
            }
        }
        cout << "INFO " << length << " : " << index << " : " << tIndex << endl;
        //cout << "TABLE LENGTH " << tableLength << ", LENGTH " << length << endl;
    }

    LinkedItem<T> *getItem(int index) {
        if (index < 0 || index >= length) {
            return NULL;
        }
        LinkedItem<T> *item = head;

        int i = 0;
        while (i < index) {
            if (item->getNext() != NULL)
                item = item->getNext();
            i++;
        }
        return item;
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
        if (length <= TABLE_SIZE) {
            tableLength = length;
            indexTable[tableLength - 1].index = 0;
            indexTable[tableLength - 1].item = NULL;
        }
        cout << "TABLE LENGTH " << tableLength << ", LENGTH " << length << endl;
    }

    void clear() {
        if (length < 1) return;
        int length = this->length;
        for (int i = 0; i < length; i++) {
            remove(this->length - 1);
        }
    }

    void printTable() {
        for (int i = 0; i < tableLength; i++) {
            cout << "TABLE ITEM: " << indexTable[i].index << " : " << indexTable[i].item->getData() << endl;
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
