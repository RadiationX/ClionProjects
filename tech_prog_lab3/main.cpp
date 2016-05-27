#include <iostream>
#include "LinkedList.h"


using namespace std;


class Item {
public:
    float key = 0;
    float fieldFloat = 0;
    char fieldChar = '\0';
};

LinkedList<Item> linkedList;


int main() {
    Item item;
    item.key = 0;
    //linkedList.addBegin(item);

    for (int i = 0; i < 15; i++) {
        item.key += 10;
        linkedList.addBegin(item);
        //linkedList.add(item);
        //linkedList.add(item, 1);
        //linkedList.printData();
    }
    linkedList.printData();
    linkedList.add(item, 7);

    cout << endl << "FINISH" << endl;
    linkedList.printData();


    return 0;
}