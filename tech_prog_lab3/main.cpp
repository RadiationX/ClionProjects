#include <iostream>
#include "LinkedList.h"

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
LinkedList<Item, 5> linkedList;
Item item;
void print(){
    for(int i = 0; i<=linkedList.getSize(); i++){
        for(int j = 0; j<linkedList.getBlock(i).getSize(); j++){
            cout<<"Block["<<i<<"] Item["<<j<<"]:\t"<<linkedList.getBlock(i).get(j).getData().key<<endl;
        }
        cout<<endl;
    }
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

    item.key +=100;
    linkedList.addFirst(item);
    print();

    return 0;
}