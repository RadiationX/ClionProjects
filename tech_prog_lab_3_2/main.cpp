//
// Created by radiationx on 09.03.17.
//
#include <iostream>
#include "LinkedList.h"

using namespace std;

int main() {
    cout << "test" << endl;
    LinkedList<int> linkedList;
    for (int i = 0; i < 7; i++) {
        //linkedList.addTail((i + 1) * 11);
        linkedList.addTail((i + 1) * 10);
        //linkedList.addTail(i+1);
    }
    linkedList.print();
    linkedList.printTable();
    linkedList.remove(6);
    linkedList.print();
    linkedList.printTable();
    linkedList.remove(5);
    linkedList.print();
    linkedList.printTable();
    return 0;
}

