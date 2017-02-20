#include <iostream>
#include "MergeSort.h"

using namespace std;


int mainSize,
        maxNumber = 90;

/*struct Item {
    int numbers[3];
};*/


class Item : BaseItem<int> {
public:
    Item() {}

    using BaseItem::isNull;
    using BaseItem::setData;
    using BaseItem::getData;
};

void printArray(Item *array, int cols);

void printArray(Item **array, int cols, int rows);

template<class E>
class SortListener : public BaseSortListener<E> {  // Prints the length of observed string into std::cout
public:
    virtual bool onMergeCompare(E &el1, E &el2) {
        return el1.getData() >= el2.getData();
    }

    virtual void onChangeArray(const std::string &title, E *mainArray, int cols) {
        cout << endl << title << endl;
        printArray(mainArray, cols);
    }

    virtual void onChangeTapeArray(const std::string &title, E **tapeArray, int cols, int rows) {
        cout << endl << title << endl;
        printArray(tapeArray, cols, rows);
    }

    virtual void onSortTape(E *tape, int size) {
        E tmp;
        for (int step = size / 2; step > 0; step /= 2) {
            for (int i = step, j; i < size; i++) {
                tmp = tape[i];
                for (j = i; j >= step; j -= step) {
                    if (tmp.getData() < tape[j - step].getData()) {
                        tape[j] = tape[j - step];
                    } else
                        break;
                }
                tape[j] = tmp;
            }
        }
    }
};


int main() {
    //srand(time(NULL));
    MergeSort<Item> mergeSort(new SortListener<Item>());

    cout << "Enter the number of elements: ";
    cin >> mainSize;
    Item *mainArray = new Item[mainSize];
    for (int i = 0; i < mainSize; i++)
        for (int j = 0; j < 3; ++j)
            mainArray[i].setData(10 + rand() % maxNumber);


    mergeSort.sort(mainArray, mainSize);
    for (int i = 1; i < mainSize; i++) {
        if (mainArray[i].getData() < mainArray[i - 1].getData()) {
            cerr << "Error: Data not sorted (i=" << i << ", el[i]=" << mainArray[i].getData() << ", el[i-1]="
                 << mainArray[i - 1].getData() << ")" << endl;
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
            cout << array[i].getData();
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
                cout << array[i][j].getData();
            }
            if (j + 1 != rows) cout << ", ";
        }
        cout << "]" << endl;
    }
}