#include <iostream>
#include "LinkedList.h"

#define blockSize 10
using namespace std;


class Item {
public:
    float key;
    float fieldFloat;
    char fieldChar;
};

LinkedList<Item, blockSize> linkedList;
Item item;

void print() {
    int block;
    int item;
    int size = linkedList.getSize();
    cout << "SIZE " << size <<" : AllocSize "<<linkedList.getAllocSize()<< endl;
    for (int i = 0; i < size; i++) {
        block = i / blockSize;
        item = i % blockSize;
        cout << i << ": Block[" << block << "] Item[" << item << "]:\t" <<
        linkedList.array[block].items[item].getData().key << endl;
    }
    cout << "SIZE " << size <<" : AllocSize "<<linkedList.getAllocSize()<< endl;
    /*for(int i = 0; i<=linkedList.getSize(); i++){
        for(int j = 0; j<linkedList.getBlock(i).getSize(); j++){
            cout<<"Block["<<i<<"] Item["<<j<<"]:\t"<<linkedList.getBlock(i).get(j).getData().key<<endl;
        }
        cout<<endl;
    }*/
}

int main() {
    item.key = 0;
    item.fieldFloat = 10;
    item.fieldChar = 'l';

    for (int i = 0; i < 7; i++) {
        item.key += 10;
        linkedList.add(item);
    }
    print();

    cout << endl << endl;

    item.key = 228;
    linkedList.add(item, 9);
    linkedList.add(item, 9);
    item.key = 332;
    linkedList.addBegin(item);
    linkedList.add(item, 15);
    print();
    linkedList.add(item, 33);
    //linkedList.add(item, 20480);

    print();

    return 0;
}