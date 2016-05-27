#include <iostream>
#include <cstring>
#include "LinkedList.h"


using namespace std;


class Item {
public:
    float key = 0;
    float fieldFloat[3] = {1, 2, 3};
    char fieldChar = '\0';
};

LinkedList<Item> list;


int main() {
    Item item;
    item.key = 0;
    for (int i = 0; i < 8; i++) {
        item.key += 10;
        list.addBegin(item);
        //list.add(item);
        //list.add(item, 1);
        //list.printData();
    }
    item.key = 228;
    list.add(item, 5);
    list.printData();
    Item temp;
    int i = 0;
    list.startSeqAccess();
    while (list.get(temp)) {
        cout << "SEQ " << i << " : " << temp.key << endl;
        i++;
    }
    list.stopSeqAccess();
    cout << endl << "FINISH" << endl;

    //list.printHex();

    return 0;
}