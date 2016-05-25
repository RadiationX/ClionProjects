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

    for(int i = 0; i<9;i++){
        item.key+=10;
        linkedList.addBegin(item);
        //linkedList.add(item);
    }
    for(int i = 0; i<11;i++){
        item.key+=10;
        //linkedList.addBegin(item);
        linkedList.add(item, i);
    }

    //linkedList.printData();
    item.key = 332;
    linkedList.add(item, 8);
    linkedList.addBegin(item);
    linkedList.addBegin(item);
    linkedList.addBegin(item);
    linkedList.addBegin(item);
    linkedList.addBegin(item);
    linkedList.addBegin(item);
    linkedList.addBegin(item);
    linkedList.addBegin(item);
    linkedList.addBegin(item);
    item.key = 1337;
    linkedList.add(item);

    cout<<endl<<"FINISH"<<endl;
    linkedList.printData();

    cout<<"LOL"<<endl;
    for(int i = 0; i<linkedList.size();i++){
        cout<<linkedList.get(i).key<<endl;
    }




    return 0;
}