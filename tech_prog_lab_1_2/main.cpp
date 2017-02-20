#include <iostream>
#include "MergeSort.h"
//#include "/sdcard/tech_prog_lab_1_2/MergeSort.h"

using namespace std;


int mainSize = 0;

class Item : BaseItem<char *> {
public:
    Item() {}

    using BaseItem::isNull;
    using BaseItem::setKey;
    using BaseItem::getKey;
};

void printArray(Item *array, int cols);

void printArray(Item **array, int cols, int rows);

template<class E>
class SortListener : public BaseSortListener<E> {
public:
    virtual bool onMergeCompare(E &el1, E &el2) {
        if (!el1.isNull() & !el2.isNull())
            return strcmp(el1.getKey(), el2.getKey()) >= 0;

        return !el1.isNull() & el2.isNull();
    }

    virtual bool onSortCompare(E &el1, E &el2) {
        if (!el1.isNull() & !el2.isNull())
            return strcmp(el1.getKey(), el2.getKey()) < 0;

        return el1.isNull() & !el2.isNull();
    }

    virtual int onChangeArray(const std::string &title, E *mainArray, int cols) {
        cout << endl << title << endl;
        printArray(mainArray, cols);
        return 0;
    }

    virtual int onChangeTapeArray(const std::string &title, E **tapeArray, int cols, int rows) {
        cout << endl << title << endl;
        printArray(tapeArray, cols, rows);
        return 0;
    }

    virtual int onSortTape(E *tape, int size) {
        E tmp;
        for (int step = size / 2; step > 0; step /= 2) {
            for (int i = step, j; i < size; i++) {
                tmp = tape[i];
                for (j = i; j >= step; j -= step) {
                    if (onSortCompare(tmp, tape[j - step])) {
                        tape[j] = tape[j - step];
                    } else
                        break;
                }
                tape[j] = tmp;
            }
        }
        return 0;
    }
};


int main() {
    //srand(time(NULL));
    MergeSort<Item> mergeSort(new SortListener<Item>());

    cout << "Enter the number of elements: ";
    cin >> mainSize;
    Item *mainArray = new Item[mainSize];
    for (int i = 0; i < mainSize; i++) {
        char *chaas = new char[2];
        for (int j = 0; j < 2; ++j) {
            chaas[j] = 'Z' - i % 24;
        }
        mainArray[i].setKey(chaas);
    }


    mergeSort.sort(mainArray, mainSize);
    for (int i = 1; i < mainSize; i++) {
        if (mergeSort.getListener()->onSortCompare(mainArray[i], mainArray[i - 1])) {
            cerr << "Error: Data not sorted (i=" << i << ", el[i]=" << mainArray[i].getKey() << ", el[i-1]="
                 << mainArray[i - 1].getKey() << ")" << endl;
            break;
        }
    }
    return 0;
}

void printArray(Item *array, int cols) {
    cout << "[";
    for (int i = 0; i < cols; i++) {
        if (array[i].isNull()) {
            cout << "--";
        } else {
            cout << array[i].getKey();
        }
        if (i + 1 != cols) cout << ", ";
    }
    cout << "]" << endl;
}

void printArray(Item **array, int cols, int rows) {
    for (int i = 0; i < cols; i++) {
        cout << "[";
        for (int j = 0; j < rows; ++j) {
            if (array[i][j].isNull()) {
                cout << "--";
            } else {
                cout << array[i][j].getKey();
            }
            if (j + 1 != rows) cout << ", ";
        }
        cout << "]" << endl;
    }
}