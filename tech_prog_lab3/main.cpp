#include <iostream>
#include "LinkedList.h"

using namespace std;

int main() {
    LinkedList<int> linkedList;
    linkedList.add(1);
    linkedList.add(2);
    linkedList.add(3);
    linkedList.add(2);
    linkedList.add(5);
    linkedList.add(7);
    linkedList.add(10);

    for(int i = 0; i<linkedList.getSize(); i++){
        cout<<"Element "<<i<<": "<<linkedList.get(i)<<endl;
    }
    return 0;
}