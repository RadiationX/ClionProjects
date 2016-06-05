#include <iostream>
#include <string>
#include "LinkedList.h"

#define fieldSize 2


using namespace std;


class Item {
public:
    float key = 0;
    float fieldFloat[fieldSize] = {0, 0};
    char fieldChar[fieldSize] = {'a', 'a'};
};

LinkedList<Item> list;

void addBegin();

void addEnd();

void addPos();

void remove();

void change();

void clear();

void search();

void print();

void printService();


int main() {
    string error = "No this item menu!";
    string title;
    title += "\n--------MENU--------\n";
    title += "1. Add begin\n";
    title += "2. Add end\n";
    title += "3. Add to position\n";
    title += "4. Remove element\n";
    title += "5. Change element\n";
    title += "6. Clear list\n";
    title += "7. Find element\n";
    title += "8. Print list elements\n";
    title += "9. Print service info\n";
    title += "10. Exit\n";
    title += "Your choice: ";
    int choose = -1;
    for (; ;) {
        cout << title;
        cin >> choose;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10, '\n');
            continue;
        }
        switch (choose) {
            case (1):
                addBegin();
                break;
            case (2):
                addEnd();
                break;
            case (3):
                addPos();
                break;
            case (4):
                remove();
                break;
            case (5):
                change();
                break;
            case (6):
                clear();
                break;
            case (7):
                search();
                break;
            case (8):
                print();
                break;
            case (9):
                printService();
                break;
            case (10):
                return 0;
            default:
                cout << error << endl;
                break;
        }
    }
    return 0;
}

Item newItem(string title) {
    cout << endl << title << endl;
    Item item;
    cout << "Key field: ";
    cin >> item.key;
    /*cout<<"Key float["<<fieldSize<<"]"<<endl;
    for(int i = 0; i< fieldSize; i++){
        cout<<"\tfloat["<<i<<"]:";
        cin>>item.fieldFloat[i];
    }
    cout<<"Key char["<<fieldSize<<"]"<<endl;
    for(int i = 0; i< fieldSize; i++){
        cout<<"\tchar["<<i<<"]:";
        cin>>item.fieldChar[i];
    }*/
    return item;
}

void addBegin() {
    list.addBegin(newItem("NEW ITEM"));
}

void addEnd() {
    list.add(newItem("NEW ITEM"));
}

void addPos() {
    Item item = newItem("NEW ITEM");
    int index = 0;
    cout << "Position: ";
    cin >> index;
    list.add(item, index);
}

void remove() {
    if (list.isEmpty()) {
        cout << "\nList is empty\n" << endl;
        return;
    }
    int index = 0;
    cout << "\nREMOVE\n";
    cout << "Position: ";
    cin >> index;
    list.remove(index);
}

void change() {
    if (list.isEmpty()) {
        cout << "\nList is empty\n" << endl;
        return;
    }
    int index = 0;
    cout << "\nCHANGE\n";
    cout << "Position: ";
    cin >> index;
    list.set(newItem("NEW ITEM"), index);
}

void clear() {
    if (list.isEmpty()) {
        cout << "\nList already empty\n" << endl;
        return;
    }
    list.clear();
}

void printItem(Item item, int i) {
    cout << "Item " << i << "\t{" << item.key << ", {" << item.fieldFloat[0] << ", " << item.fieldFloat[1] << "}, {" <<
    item.fieldChar[0] << ", " << item.fieldChar[1] << "}" << endl;
}

void search() {
    if (list.isEmpty()) {
        cout << "\nList is empty\n" << endl;
        return;
    }
    Item item, temp;
    item = newItem("SEARCH");
    int i = 0;
    list.startSeqAccess();
    while (list.get(temp)) {
        i++;
        if (temp.key != item.key)
            continue;
        if (!(temp.fieldFloat[0] == item.fieldFloat[0] && temp.fieldFloat[1] == item.fieldFloat[1]))
            continue;
        if (!(temp.fieldChar[0] == item.fieldChar[0] && temp.fieldChar[1] == item.fieldChar[1]))
            continue;
        printItem(temp, i - 1);
    }

}

void print() {
    if (list.isEmpty()) {
        cout << "\nList is empty\n" << endl;
        return;
    }
    int i = 0;
    list.startSeqAccess();
    Item item;
    while (list.get(item)) {
        printItem(item, i);
        i++;
    }
    list.stopSeqAccess();
}

void printService() {
    cout << "\nSERVICE DATA\n";
    cout << "List size: " << list.size() << endl;
    cout << "Blocks number: " << list.blocks() << endl;
    cout << "Block size: " << list.getBlockSize() << endl;

    if (list.isEmpty()) {
        cout << "\nList is empty\n" << endl;
        return;
    }
    int i = 0;
    list.startSeqAccess();
    Item item;
    while (list.get(item, true)) {
        printItem(item, i);
        i++;
    }
    list.stopSeqAccess();
}