#include <iostream>
#include "LinkedList.h"

using namespace std;



class item{
public:
    float key;
    float fieldFloat;
    char fieldChar;
};


int main() {
    LinkedList<item, 5> linkedList;

    linkedList.add({228.228,2,'1'});

    cout<<linkedList.get(0).key;
    return 0;
}