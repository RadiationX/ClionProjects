//
// Created by radiationx on 07.02.17.
//

#ifndef TECH_PROG_LAB_1_2_MERGESORT_H
#define TECH_PROG_LAB_1_2_MERGESORT_H

#include <iostream>
#include <cmath>

using namespace std;


template<class E>
class BaseSortListener {
public:
    BaseSortListener() {}

    ~BaseSortListener() {}

    virtual bool OnCompare(E &el1, E &el2, int index) = 0;

    virtual void OnChangeArray(const std::string &title, E *mainArray, int size) = 0;

    virtual void OnChangeTapeArray(const std::string &title, E **tapeArray, int size) = 0;

    virtual void OnSortTape(E *tape, int size, int index) = 0;
};

template<class E>
class MergeSort {
private:
    BaseSortListener<E> *listener;
    bool initialized = false;
    int maxNumber = 90,
            selectIndex = 0,
            NULL_ELEMENT = -1;

public:
    MergeSort(BaseSortListener<E> *listener) {
        this->listener = listener;
        initialized = true;
    }

    E *sort(E *mainArray, int mainSize) {
        if (!initialized) {
            cout << "Error: Need initialize listener" << endl;
            return mainArray;
        }
        listener->OnChangeArray(string("Input data:"), mainArray, mainSize);
        double sqrtMainSize = sqrt(mainSize);
        //Размерность лент
        int tapeSize = (int) (sqrtMainSize - floor(sqrtMainSize) == 0 ? sqrtMainSize : sqrtMainSize + 1);
        E **tapeArray = new E *[tapeSize];

        //----Преобразование в ленты----//
        for (int i = 0; i < tapeSize; i++)
            tapeArray[i] = new E[tapeSize];

        for (int i = 0, m = 0; i < tapeSize; i++) {
            for (int j = 0; j < tapeSize; j++, m++) {
                tapeArray[i][j] = mainArray[m];
                if (m >= mainSize)
                    for (int k = 0; k < 3; k++)
                        tapeArray[i][j].numbers[k] = NULL_ELEMENT;
            }
        }

        listener->OnChangeTapeArray(string("Transform to tapes:"), tapeArray, tapeSize);

        //----Сортировка----//
        for (int i = 0; i < tapeSize; ++i) {
            listener->OnSortTape(tapeArray[i], tapeSize, selectIndex);
        }

        listener->OnChangeTapeArray(string("Sorted tapes:"), tapeArray, tapeSize);

        //----Слияние лент----//
        int minIndex = 0,
                *index = new int[tapeSize];
        int minNumber;

        delete[](mainArray);
        mainArray = new E[mainSize];

        for (int i = 0; i < tapeSize; index[i] = 0, i++);

        for (int k = 0; k < mainSize; k++) {
            minNumber = maxNumber + 10;
            for (int i = 0; i < tapeSize; i++) {
                if (index[i] < tapeSize && minNumber > tapeArray[i][index[i]].numbers[selectIndex]) {
                    minIndex = i;
                    minNumber = tapeArray[i][index[i]].numbers[selectIndex];
                }
            }

            if (tapeArray[minIndex][index[minIndex]].numbers[selectIndex] == NULL_ELEMENT)
                k--;
            else {
                mainArray[k] = tapeArray[minIndex][index[minIndex]];
            }
            index[minIndex]++;
        }
        listener->OnChangeArray(string("Merged tapes:"), mainArray, mainSize);
        return mainArray;
    }
};


#endif //TECH_PROG_LAB_1_2_MERGESORT_H