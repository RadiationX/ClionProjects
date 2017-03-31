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
    const static int TABLE_SIZE = 4;
    struct TableItem {
        int index = 0;
        T *item = NULL;
    };
    TableItem *table = new TableItem[TABLE_SIZE];
    int length = 0;
    int interval = 0;

public:
    TableItem getItem(int index) {
        return table[index];
    }

    int getLength() {
        return length;
    }

    int getTableIndex(int listIndex) {
        int tIndex = 0;
        for (; tIndex < length; tIndex++) {
            if (listIndex <= ((tIndex > 0) ? table[tIndex].index : 0))
                break;
            if (tIndex + 1 == length)
                break;
        }
        return tIndex;
    }

    T *get(int index) {
        int tIndex = 0;
        for (; tIndex < TABLE_SIZE; tIndex++) {
            if (index <= ((tIndex > 0) ? table[tIndex].index : 0)) {
                break;
            }
        }
        T *item = table[tIndex].item;

        if (index != table[tIndex].index) {
            int border = ((table[tIndex].index - table[tIndex - 1].index) / 2) + table[tIndex - 1].index;
            if (border < index) {
                tIndex--;
            }
            item = table[tIndex].item;
            int i = table[tIndex].index;
            while (i != index) {
                if (table[tIndex].index < index) {
                    item = item->getNext();
                    i++;
                } else {
                    item = item->getPrev();
                    i--;
                }
            }
        }
        return item;
    }

    void add(T *newItem, int listIndex, int listLength) {
        int tIndex = listIndex;
        if (listLength <= TABLE_SIZE) {
            bool moved = false;
            for (int j = length; j > tIndex; j--) {
                table[j].item = table[j - 1].item;
                table[j].index = table[j - 1].index;
                table[j].index++;
                moved = true;
            }
            if (!moved) {
                table[tIndex].index = tIndex;
            }
            table[tIndex].item = newItem;
            length++;
        } else {
            tIndex = getTableIndex(listIndex);

            for (int i = tIndex == 0 ? tIndex + 1 : tIndex; i < length; i++) {
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
        cout << "REMOVE " << listIndex << " : " << listLength << endl;
        int tIndex = listIndex;
        if (listLength <= TABLE_SIZE) {
            for (int j = tIndex; j < length - 1; j++) {
                table[j].item = table[j + 1].item;
                table[j].index = table[j + 1].index;
                table[j].index--;
                if (length - 1 == j + 1) {
                    table[j + 1].item = NULL;
                    table[j + 1].index = 0;
                }
            }
            length--;
        } else {
            tIndex = getTableIndex(listIndex);

            if (table[tIndex].index == listIndex) {
                table[tIndex].item = tIndex == 0 ? table[tIndex].item->getNext() : table[tIndex].item->getPrev();
            }

            for (int i = tIndex == 0 ? tIndex + 1 : tIndex; i < length; i++) {
                table[i].index--;
            }

            if (abs(table[tIndex].index - table[tIndex - 1].index) <= 1) {
                table[tIndex - 1].index--;
            }

            restoreUniformity(listLength);
        }
    }

    void restoreUniformity(int listLength) {
        if (((listLength - length) % (length - 1) == 0)) {
            interval = (listLength - length) / (length - 1);
            cout << "NEW TABLE INTERVAL: " << interval << endl;
            for (int j = 1; j < TABLE_SIZE - 1; j++) {
                int newIndex = j + j * interval;
                table[j].item = get(newIndex);
                table[j].index = newIndex;
            }
        }
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
        indexTable.add(newItem, index, length);
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
        indexTable.remove(index, length - 1);
        remove(item);
    }

    void remove(LinkedItem<T> *item) {
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
    }

    void clear() {
        if (length < 1) return;
        int length = this->length;
        for (int i = 0; i < length; i++) {
            remove(this->length - 1);
        }
    }

    void printTable() {
        cout << endl;
        for (int i = 0; i < indexTable.getLength(); i++) {
            cout << "TABLE ITEM[" << i << "]: " << indexTable.getItem(i).index << " : "
                 << indexTable.getItem(i).item->getData()
                 << endl;
        }
        cout << endl;
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