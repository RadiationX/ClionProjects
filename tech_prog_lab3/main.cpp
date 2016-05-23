#include <iostream>
#include "LinkedList.h"


using namespace std;


class Item {
public:
    float key;
    float fieldFloat;
    char fieldChar;
};

LinkedList<Item> linkedList;


int main() {
    Item item;
    item.key = 0;

    for(int i = 0; i<64;i++){
        item.key+=10;
        linkedList.addBegin(item);
        //linkedList.add(item);
    }

    cout<<endl<<"FINISH"<<endl;
    linkedList.PrintData();




    return 0;
}