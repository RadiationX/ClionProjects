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
    LinkedItem<T> *head = NULL;
    LinkedItem<T> *tail = NULL;
    int length = 0;

public:
    void addHead(T data) {
        add(data, 0);
    }

    void addTail(T data) {
        add(data, length);
    }

    void add(T data, int index) {
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
            LinkedItem<T> *target = get(index);
            target->getPrev()->setNext(newItem);
            newItem->setPrev(target->getPrev());
            target->setPrev(newItem);
            newItem->setNext(target);
        }
        //cout << "HEAD " << head->getData() << " : TAIL " << tail->getData() << endl;
        length++;
    }

    LinkedItem<T> *get(int index) {
        if (index < 0 || index >= length) {
            return NULL;
        }
        int i = 0;
        LinkedItem<T> *item = head;
        while (i < index) {
            if (item->getNext() != NULL)
                item = item->getNext();
            i++;
        }
        return item;
    }

    void remove(int index) {
        if (index < 0 || index >= length) {
            return;
        }
        LinkedItem<T> *target = get(index);
        if (length == 1) {
            //Delete first element
            head = NULL;
            tail = NULL;
        } else if (index == 0) {
            //Remove from head
            head = target->getNext();
            head->setPrev(NULL);
            target->setNext(NULL);
        } else if (index == length - 1) {
            //Remove from tail
            tail = target->getPrev();
            tail->setNext(NULL);
            target->setPrev(NULL);
        } else {
            //Remove from position
            target->getPrev()->setNext(target->getNext());
            target->getNext()->setPrev(target->getPrev());
            target->setPrev(NULL);
            target->setNext(NULL);
        }
        delete (target);
        length--;
    }

    void clear() {
        if (length < 1)  return;
        int i = 0;
        LinkedItem<T> *item = head;
        while (i < length) {
            if (item->getNext() == NULL) delete (item);
            item = item->getNext();
            if (item != NULL) delete (item->getPrev());
            i++;
        }
        length = 0;
        head = NULL;
        tail = NULL;
    }

    void print() {
        if (length > 0) {
            int i = 0;
            LinkedItem<T> *temp = head;
            cout << endl;
            cout << "HEAD " << head->getData() << endl;
            while (temp != NULL) {
                if (i > 20) {
                    cout << "SUUUUKA" << endl;
                    return;
                }
                cout << "[" << i << "] " << temp->getData() << endl;
                temp = temp->getNext();
                i++;
            }
            cout << "TAIL " << tail->getData() << endl;
        }

        cout << "SIZE " << size() << endl;
        cout << endl;
    }

    int size() {
        return length;
    }
};

#endif //CLIONPROJECTS_LINKEDLIST_H
