//
// Created by radiationx on 09.03.17.
//
#include <iostream>
#include "LinkedList.h"

using namespace std;

int main() {
    cout << "test" << endl;
    LinkedList<int> linkedList;
    for (int i = 0; i < 13; i++) {
        //linkedList.addTail((i + 1) * 11);
        linkedList.addTail((i + 1) * 10);
    }
    for (int i = 0; i < 13; i++) {
        //linkedList.addTail((i + 1) * 11);
        linkedList.addHead((i + 1) * 10);
    }
    /*linkedList.addTail(10);
    linkedList.addTail(20);
    linkedList.addTail(30);
    linkedList.addTail(40);*/
    cout << endl;

    /*linkedList.add(1337, 2);
    linkedList.add(1337, 8);
    linkedList.add(1337, 12);
    linkedList.add(1338, 8);
    linkedList.add(1338, 2);*/
    //linkedList.add(1339, 5);

    linkedList.print();
    cout << endl << endl;
    linkedList.printTable();
    cout << endl << endl;
    /*int size = linkedList.size();
    for (int i = 0; i < size; i++){
        linkedList.getByTable(i);
    }*/
    /*linkedList.getByTable(0);
    linkedList.getByTable(2);
    linkedList.getByTable(7);
    linkedList.getByTable(10);
    linkedList.getByTable(16);*/
    //system("pause");
    return 0;
}

