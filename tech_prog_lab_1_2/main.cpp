#include <iostream>
#include "MergeSort.h"
#include <unistd.h>
//#include "/sdcard/tech_prog_lab_1_2/MergeSort.h"

using namespace std;


int mainSize = 0;

class Item : BaseItem<int> {
public:
    Item() {}

    using BaseItem::isNull;
    using BaseItem::setKey;
    using BaseItem::getKey;
};

void printArray(Item *array, int cols);

void printArray(Item **array, int cols, int rows);

bool checkSorted(Item *mainArray, int iteration);

template<class E>
class SortListener : public BaseSortListener<E> {
public:
    using BaseSortListener<E>::safeOnSortCompare;

    virtual bool onMergeCompare(E &el1, E &el2) {
        return el1.getKey() <= el2.getKey();
    }

    virtual bool onSortCompare(E &el1, E &el2) {
        return el1.getKey() < el2.getKey();
    }

    virtual int onSortTape(E *tape, int size) {
        E tmp;
        for (int step = size / 2; step > 0; step /= 2) {
            for (int i = step, j; i < size; i++) {
                tmp = tape[i];
                for (j = i; j >= step; j -= step) {
                    if (safeOnSortCompare(tmp, tape[j - step])) {
                        tape[j] = tape[j - step];
                    } else
                        break;
                }
                tape[j] = tmp;
            }
        }
        return 0;
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
};

MergeSort<Item> mergeSort(new SortListener<Item>());

int main() {
    srand(time(NULL));

    cout << "Enter the number of elements: ";
    //cin >> mainSize;
    mainSize = 82;
    int tests = 1;
    int j = 0;
    for (; j < tests; j++) {
        cout << "TEST ITERATION " << j << " -------------------------------- open" << endl;
        Item *mainArray = new Item[mainSize];
        for (int i = 0; i < mainSize; i++)
            mainArray[i].setKey(10 + rand() % 90);
        mainArray = mergeSort.sort(mainArray, mainSize);

        if (!checkSorted(mainArray, j)) break;
        cout << endl;
        cout << "TEST ITERATION " << j << " -------------------------------- close : NO ERROR" << endl << endl << endl;
        delete[](mainArray);

        //For escape lag
        usleep(10 * 1000);
    }
    if (j >= tests) {
        cout << "ALL TESTS PASSED" << endl;
    }
    return 0;
}

bool checkSorted(Item *mainArray, int iteration) {
    for (int i = 1; i < mainSize; i++) {
        if (mergeSort.getListener()->safeOnSortCompare(mainArray[i], mainArray[i - 1])) {
            cout << "TEST ITERATION " << iteration << " : ERROR: Data not sorted (i=" << i << ", el[i]="
                 << mainArray[i].getKey() << ", el[i-1]="
                 << mainArray[i - 1].getKey() << ")" << endl;
            return false;
        }
    }
    return true;
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