//
// Created by radiationx on 09.03.17.
//
#include <iostream>
#include "LinkedList.h"

using namespace std;

int main() {
    cout << "test" << endl;
    LinkedList<int> linkedList;
    for (int i = 0; i < 10; i++) {
        linkedList.addTail(i);
    }
    linkedList.print();
    /*for (int i = 0; i < 5; i++) {
        linkedList.remove(0);
    }
    for (int i = 0; i < 5; i++) {
        linkedList.remove(linkedList.size() - 1);
    }
    linkedList.print();*/

    linkedList.clear();
    linkedList.print();
    /*for (int i = 0; i < 10; i++) {
        linkedList.addTail(i);
    }*/
    return 0;
}

