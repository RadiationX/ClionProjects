#include <iostream>
#include "LinkedList.h"
#define blockSize 10
using namespace std;



class Item{
public:
    float key;
    float fieldFloat;
    char fieldChar;
    float getKey(){
        return key;
    }
};
LinkedList<Item, blockSize> linkedList;
Item item;
void print(){
    int block;
    int item;
    int size = linkedList.getSize();
    cout<<"SIZE "<<size<<endl;
    for(int i = 0; i<size; i++){
        block = i/blockSize;
        item = i%blockSize;
        cout<<"Block["<<block<<"] Item["<<item<<"]:\t"<<linkedList.getBlock(block).get(item).getData().key<<endl;
    }
    /*for(int i = 0; i<=linkedList.getSize(); i++){
        for(int j = 0; j<linkedList.getBlock(i).getSize(); j++){
            cout<<"Block["<<i<<"] Item["<<j<<"]:\t"<<linkedList.getBlock(i).get(j).getData().key<<endl;
        }
        cout<<endl;
    }*/
}
int main() {
    item.key=1337.111;
    item.fieldFloat = 1337;
    item.fieldChar = 'l';

    for(int i=0; i<7;i++){
        item.key+=10;
        linkedList.add(item);
    }
    print();

    cout<<endl<<endl;

    item.key = 228;
    linkedList.add(item, 2);
    item.key = 322;
    linkedList.addFirst(item);
    linkedList.add(item, 15);
    print();

    return 0;
}