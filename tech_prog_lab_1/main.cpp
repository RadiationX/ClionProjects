#include <iostream>
#include <math.h>

using namespace std;

int mainSize,
        tapeSize,
        maxNumber = 90,
        selectIndex = 0,
        NULL_ELEMENT = -1;

struct Element {
    int numbers[3];
};

void printMainArray(Element *array);

void printTapeArray(Element **array);

int main() {
    //srand(time(NULL));

    cout << "Введите количество элементов: ";
    cin >> mainSize;

    double sqrtMainSize = sqrt(mainSize);
    //Размерность лент
    tapeSize = (int) (sqrtMainSize - floor(sqrtMainSize) == 0 ? sqrtMainSize : sqrtMainSize + 1);

    Element *mainArray = new Element[mainSize];
    Element **tapeArray = new Element *[tapeSize];

    for (int i = 0; i < mainSize; i++)
        for (int j = 0; j < 3; ++j)
            mainArray[i].numbers[j] = 10 + rand() % maxNumber;

    cout << endl << "Изначальные данные:" << endl;
    printMainArray(mainArray);
    cout << endl;


    //----Преобразование в ленты----//
    for (int i = 0; i < tapeSize; i++)
        tapeArray[i] = new Element[tapeSize];

    for (int i = 0, m = 0; i < tapeSize; i++) {
        for (int j = 0; j < tapeSize; j++, m++) {
            tapeArray[i][j] = mainArray[m];
            if (m >= mainSize)
                for (int k = 0; k < 3; k++)
                    tapeArray[i][j].numbers[k] = NULL_ELEMENT;
        }
    }

    cout << "Преобразование в ленты:" << endl;
    printTapeArray(tapeArray);
    cout << endl;


    //----Сортировка----//
    Element element;
    for (int i = 0; i < tapeSize; ++i)
        for (int j = 0; j < tapeSize; ++j)
            for (int k = 0; k < tapeSize; ++k)
                if (tapeArray[i][j].numbers[selectIndex] < tapeArray[i][k].numbers[selectIndex]) {
                    element = tapeArray[i][j];
                    tapeArray[i][j] = tapeArray[i][k];
                    tapeArray[i][k] = element;
                }


    cout << "Сортированные ленты:" << endl;
    printTapeArray(tapeArray);
    cout << endl;


    //----Слияние лент----//
    int minIndex = 0,
            *index = new int[tapeSize];
    int minNumber;

    delete[](mainArray);
    mainArray = new Element[mainSize];

    for (int i = 0; i < tapeSize; index[i] = 0, i++);

    for (int k = 0; k < mainSize; k++) {
        minNumber = maxNumber + 10;
        for (int i = 0; i < tapeSize; i++) {
            cout<<"compare(i = "<<i<<"): "<<index[i]<<" < "<<tapeSize<<" && "<<minNumber<<" > "<<tapeArray[i][index[i]].numbers[selectIndex]<<" : "<<((index[i] < tapeSize && minNumber > tapeArray[i][index[i]].numbers[selectIndex])?"true":"false")<<endl;
            if (index[i] < tapeSize && minNumber > tapeArray[i][index[i]].numbers[selectIndex]) {
                minIndex = i;
                minNumber = tapeArray[i][index[i]].numbers[selectIndex];
            }
        }

        if (tapeArray[minIndex][index[minIndex]].numbers[selectIndex] == NULL_ELEMENT)
            k--;
        else{
            cout<<"move to "<<k<<" : "<<tapeArray[minIndex][index[minIndex]].numbers[selectIndex]<<endl<<endl;
            mainArray[k] = tapeArray[minIndex][index[minIndex]];
        }

        index[minIndex]++;
    }

    cout << "Слияние лент:" << endl;
    printMainArray(mainArray);
    return 0;
}

void printMainArray(Element *array) {
    for (int i = 0; i < mainSize; i++) {
        cout << "{";
        for (int j = 0; j < 3; ++j)
            cout << array[i].numbers[j] << (j != 2 ? " " : "");
        cout << "}" << endl;
    }
}

void printTapeArray(Element **array) {
    for (int i = 0; i < tapeSize; i++) {
        for (int j = 0; j < tapeSize; ++j) {
            cout << "{";
            for (int k = 0; k < 3; k++)
                cout << array[i][j].numbers[k] << (k != 2 ? " " : "");
            cout << "} ";
        }
        cout << endl;
    }
}