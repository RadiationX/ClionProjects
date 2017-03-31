//
// Created by radiationx on 09.03.17.
//
#include <iostream>
#include "LinkedList.h"

using namespace std;

int main() {
    cout << "test" << endl;
    LinkedList<int> linkedList;
    for (int i = 0; i < 19; i++) {
        //linkedList.addTail((i + 1) * 11);
        linkedList.addTail(i);
    }
    cout << endl;

    /*linkedList.add(1488, 5);
    linkedList.add(1488, 5);
    linkedList.add(1488, 5);
    linkedList.add(1490, 5);
    linkedList.add(1490, 5);*/
    //linkedList.add(1488, 5);

    linkedList.print();
    /*int size = linkedList.size();
    for (int i = 0; i < size; i++) {
        cout << "SUKA "<<i<<" : " << linkedList.get(i) << endl;
    }*/
    cout << endl << endl;
    linkedList.printTable();
    return 0;
}

