
#include "Search.h"
//#include "/sdcard/tech_prog_lab_2_2/Search.h"
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class Item {
private:
    float key[3];
    char *fieldOne;
    int fieldTwo;
public:
    float *getKey() {
        return key;
    }

    char *getFieldOne() {
        return fieldOne;
    }

    void setFieldOne(char *value) {
        fieldOne = value;
    }

    int getFieldTwo() {
        return fieldTwo;
    }

    void setFieldTwo(int value) {
        fieldTwo = value;
    }
};

class CatalogItem : BaseItem<float> {
private:
    Item *itemPointer;
public:
    CatalogItem() {}

    using BaseItem::isNull;
    using BaseItem::setKey;
    using BaseItem::getKey;

    void setItem(Item *item) {
        itemPointer = item;
    }

    Item *getItem() {
        return itemPointer;
    }
};

template<class T, typename I, typename K>
class BlockSearchMethod : public SearchMethod<T, I, K> {
public:
    virtual int onCallSearch(K arg, T *catalog, int catalogSize) {
        int blockCount = (int) sqrt(catalogSize);
        //resIndex take last index value for correct find borders
        int resIndex = -1;
        for (int i = blockCount; i < catalogSize; i += blockCount) {
            resIndex = i;
            if (catalog[i].getKey() >= arg) {
                for (int j = i; j > i - blockCount; j--) {
                    resIndex = j;
                    if (catalog[j].getKey() <= arg) break;
                }
                break;
            }
        }
        return resIndex;
    }
};

Search<CatalogItem, Item, float> blockSearch(new BlockSearchMethod<CatalogItem, Item, float>());

void initMenu();

void printItem(Item *item);

void printCatalogItem(CatalogItem *item);

int main() {
    int mainSize = 0;
    cout << "Enter the number of items: ";
    cin >> mainSize;
    Item *mainArray = new Item[mainSize];

    //Fill main array
    for (int i = 0; i < mainSize; i++) {
        Item *item = &mainArray[i];
        for (int j = 0; j < 3; j++) {
            item->getKey()[j] = 10 + rand() % 90;
        }
        char *fieldOne = new char[2];
        for (int j = 0; j < 2; ++j)
            fieldOne[j] = 'Z' - i % 24;
        item->setFieldOne(fieldOne);
        item->setFieldTwo(10 + rand() % 90);
    }
    cout << "Generated items:" << endl;
    for (int i = 0; i < mainSize; i++) {
        cout << "[" << i << "] : ";
        printItem(&mainArray[i]);
        cout << endl;
    }
    cout << endl;

    //Create catalog
    blockSearch.createCatalog(mainArray, mainSize);
    cout << "Created catalog:" << endl;
    for (int i = 0; i < mainSize; i++) {
        cout << "[" << i << "] : ";
        printCatalogItem(&blockSearch.getCatalog()[i]);
        cout << endl;
    }
    initMenu();


    return 0;
}

void printItem(Item *item) {
    cout << "[[";
    for (int j = 0; j < 3; j++) {
        cout << item->getKey()[j];
        if (j != 2)
            cout << ", ";
    }
    cout << "], " << item->getFieldOne() << ", " << item->getFieldTwo() << "]";
}

void printCatalogItem(CatalogItem *item) {
    cout << "[" << item->getKey() << ", *";
    printItem(item->getItem());
    cout << "]";
}

void initMenu() {
    cout << endl;
    int action = -1;
    int *result;
    for (; action != 0;) {
        cout << "---------- MENU ----------" << endl;
        cout << "1 - Search by equals" << endl << "2 - Search by interval" << endl << "0 - Exit" << endl << endl;
        cout << "Choice action: ";
        cin >> action;
        switch (action) {
            case 1:
                int a;
                cout << "Enter argument: ";
                cin >> a;
                result = blockSearch.find(a);
                break;
            case 2:
                int a1, a2;
                cout << "Enter first argument: ";
                cin >> a1;
                cout << "Enter second argument: ";
                cin >> a2;
                result = blockSearch.find(a1, a2);
                break;
            case 0:
                return;
            default:
                continue;
        }
        cout << endl << "Found items:" << endl;
        if (result[0] == -1) {
            cout << "No items!" << endl;
        } else {
            for (int i = result[0], j = 0; i <= result[1]; i++, j++) {
                cout << "[" << j << "] : *";
                printItem(blockSearch.getCatalog()[i].getItem());
                cout << endl;
            }
        }
        cout << endl;
    }
}

