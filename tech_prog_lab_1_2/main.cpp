#include <iostream>
#include "MergeSort.h"

using namespace std;


int mainSize,
        maxNumber = 90;

/*struct Item {
    int numbers[3];
};*/

class Item {
public:
    int numbers[3];

    Item() {
    }

    ~Item() {

    }
};

void printMainArray(Item *array, int size);

void printTapeArray(Item **array, int size);

template<class E>
class SortListener : public BaseSortListener<E> {  // Prints the length of observed string into std::cout
public:
    virtual bool OnCompare(E &el1, E &el2, int index) {
        return el1.numbers[index] < el2.numbers[index];
    }

    virtual void OnChangeArray(const std::string &title, E *mainArray, int size) {
        cout << endl << title << endl;
        printMainArray(mainArray, size);
    }

    virtual void OnChangeTapeArray(const std::string &title, E **tapeArray, int size) {
        cout << endl << title << endl;
        printTapeArray(tapeArray, size);
    }

    virtual void OnSortTape(E *tape, int size, int index) {
        E tmp;
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                if (OnCompare(tape[j], tape[k], index)) {
                    tmp = tape[j];
                    tape[j] = tape[k];
                    tape[k] = tmp;
                }
            }
        }
    }
};


int main() {
    //srand(time(NULL));
    MergeSort<Item> mergeSort(new SortListener<Item>());

    cout << "Введите количество элементов: ";
    cin >> mainSize;
    Item *mainArray = new Item[mainSize];
    for (int i = 0; i < mainSize; i++)
        for (int j = 0; j < 3; ++j)
            mainArray[i].numbers[j] = 10 + rand() % maxNumber;

    mergeSort.sort(mainArray, mainSize);
    return 0;
}

void printMainArray(Item *array, int size) {
    for (int i = 0; i < size; i++) {
        cout << "{";
        for (int j = 0; j < 3; ++j)
            cout << array[i].numbers[j] << (j != 2 ? " " : "");
        cout << "}" << endl;
    }
}

void printTapeArray(Item **array, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; ++j) {
            cout << "{";
            for (int k = 0; k < 3; k++)
                cout << array[i][j].numbers[k] << (k != 2 ? " " : "");
            cout << "} ";
        }
        cout << endl;
    }
}