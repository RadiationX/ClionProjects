//
// Created by radiationx on 09.03.17.
//
#include <iostream>
#include "LinkedList.h"

using namespace std;

int main() {
    cout << "test" << endl;
    LinkedList<int> linkedList;
    for (int i = 0; i < 4; i++) {
        //linkedList.addTail((i + 1) * 11);
        linkedList.addTail((i + 1) * 10);
        //linkedList.addTail(i);
    }

    linkedList.print();
    linkedList.printTable();
    linkedList.remove(linkedList.size() - 2);
    linkedList.remove(linkedList.size() - 1);
    linkedList.remove(0);
    for (int i = 0; i < 4; i++) {
        //linkedList.addTail((i + 1) * 11);
        linkedList.addHead((i + 1) * 10);
        //linkedList.addTail(i);
    }
    linkedList.print();
    linkedList.printTable();
    return 0;
}

