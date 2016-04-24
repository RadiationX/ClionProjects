#include <iostream>
#include "LinkedList.h"

using namespace std;



class Item{
public:
    float key;
    float fieldFloat;
    char fieldChar;
};


int main() {
    LinkedList<Item, 5> linkedList;

    Item item;
    item.key=1337.111;
    item.fieldFloat = 1337;
    item.fieldChar = 'l';

    linkedList.add(item);

    cout<<linkedList.get(0).key;
    return 0;
}