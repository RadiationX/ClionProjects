//
// Created by radiationx on 09.03.17.
//
#include <iostream>
#include "LinkedList.h"

using namespace std;
LinkedList<int> linkedList;

void initMenu();

int inputIndex() {
    string p1 = "";
    cout << "Enter position: ";
    cin >> p1;
    if (strcmp(p1.c_str(), "h") == 0) {
        return 0;
    }
    if (strcmp(p1.c_str(), "t") == 0) {
        return linkedList.length() - 1;
    }
    return atoi(p1.c_str());
}

int main() {
    initMenu();
    return 0;
}

void fillData() {
    int size = 0;
    cout << "Enter the number of items: ";
    cin >> size;
    char random = 'n';
    cout << "Random items [y/n]?: ";
    cin >> random;
    if (random == 'y') {
        for (int i = 0; i < size; i++) {
            linkedList.addTail(10 + rand() % 90);
        }
    } else {
        for (int i = 0; i < size; i++) {
            linkedList.addTail((i + 1) * 10);
        }
    }
}

void printItem(int index, int data) {
    cout << "[" << index << "]: " << data << endl;
}

void printTable() {
    cout << endl;
    cout << "TABLE:" << endl;
    for (int i = 0; i < linkedList.getIndexTable().length(); i++) {
        cout << "[" << i << "] = ";
        printItem(linkedList.getIndexTable().getItem(i).index, linkedList.getIndexTable().getItem(i).item->getData());
    }
    cout << "TABLE LENGTH: " << linkedList.getIndexTable().length() << endl;
    cout << endl;
}


void printList() {
    cout << "LIST:" << endl;
    if (linkedList.length() > 0) {
        int i = 0;
        LinkedItem<int> *temp = linkedList.getLinkedHead();
        cout << endl;
        cout << "HEAD: " << linkedList.getLinkedHead()->getData() << endl;
        while (temp != NULL) {
            printItem(i, temp->getData());
            temp = temp->getNext();
            i++;
        }
        cout << "TAIL: " << linkedList.getLinkedTail()->getData() << endl;
    }
    cout << "LIST LENGTH: " << linkedList.length() << endl;
    printTable();
    cout << endl;
}


void initMenu() {
    cout << endl;
    int action = -1;
    for (; action != 0;) {
        cout << "---------- MENU ----------" << endl;
        cout << "1 - Add item" << endl
             << "2 - Remove item" << endl
             << "3 - Get item" << endl
             << "4 - Print list" << endl
             << "5 - Clear list" << endl
             << "6 - Fill with random values" << endl
             << "0 - Exit"
             << endl << endl;
        cout << "Choice action: ";
        cin >> action;
        switch (action) {
            case 1: {
                int index = inputIndex();
                int data = -1;
                cout << "Enter value: ";
                cin >> data;
                linkedList.add(data, index);
                break;
            }
            case 2: {
                int index = inputIndex();
                linkedList.remove(index);
                break;
            }
            case 3: {
                int index = inputIndex();
                printItem(index, linkedList.get(index));
            }
                break;
            case 4: {
                printList();
            }
                break;
            case 5: {
                linkedList.clear();
            }
                break;
            case 6: {
                fillData();
            }
                break;
            case 0:
                return;
            default:
                continue;
        }
        cout << endl;
    }

}