//
// Created by radiationx on 09.03.17.
//
#include <iostream>
#include "LinkedList.h"

using namespace std;

int main() {
    cout << "test" << endl;
    LinkedList<int> linkedList;
    for (int i = 0; i < 18; i++) {
        //linkedList.addTail((i + 1) * 11);
        linkedList.addTail(i);
    }
    cout << endl;

    linkedList.add(1337, 5);
    linkedList.add(1337, 5);
    linkedList.add(1337, 5);
    linkedList.add(1338, 5);
    linkedList.add(1338, 5);
    //linkedList.add(1339, 5);

    linkedList.print();
    cout << endl << endl;
    linkedList.printTable();
    cout << endl << endl;
    linkedList.getByTable(0);
    linkedList.getByTable(2);
    linkedList.getByTable(7);
    linkedList.getByTable(10);
    linkedList.getByTable(16);
    return 0;
}

