//
// Created by radiationx on 23.03.17.
//

#include <iostream>

#ifndef PROG_LAB_3_2_QUEUE_H
#define PROG_LAB_3_2_QUEUE_H

using namespace std;

template<typename T>
class Queue {
    T *items;
    int first, last, maxSize;
public :
    Queue(int initSize) {
        maxSize = initSize;
        items = new T[maxSize];
        first = last = 0;
    }

    void push(T item) {
        if (last + 1 == first || (last + 1 == maxSize && !first)) {
            return;
        }
        if (last + 1 == maxSize) last = 0;
        items[last] = item;
        last++;
    }

    void pop() {
        if (first == last) {
            return;
        }
        first++;
        if (first == maxSize)
            first = 0;
    }

    void clear() {
        for (int i = first; i < last; i++)
            pop();
    }

    T front() {
        return items[first];
    }

    T back() {
        return items[last];
    }

    int frontIndex() {
        return first;
    }

    int backIndex() {
        return last;
    }

    T get(int i) {
        return items[i];
    }

    int size() {
        return last-first;
    }
};

#endif //PROG_LAB_3_2_QUEUE_H
