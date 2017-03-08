//
// Created by radiationx on 07.03.17.
//

#ifndef TECH_PROG_LAB_2_2_1_SEARCH_H
#define TECH_PROG_LAB_2_2_1_SEARCH_H

#include "MergeSort.h"
//#include "/sdcard/tech_prog_lab_2_2_1/MergeSort.h"

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
        return 0;
    }

    virtual int onChangeTapeArray(const std::string &title, E **tapeArray, int cols, int rows) {
        return 0;
    }
};

template<class T, typename I, typename K>
class SearchMethod {
public:
    SearchMethod() {}

    ~SearchMethod() {}

    virtual int onCallSearch(K arg, T *catalog, int catalogSize) {
        cerr << "onMergeCompare not overridden" << endl;
        return -1;
    }
};


template<class T, typename I, typename K>
class Search {
private:
    MergeSort<T> *mergeSort;
    SearchMethod<T, I, K> *searchMethod;
    bool initialized;

    T *catalog;
    int catalogSize;

    int getLeftBorder(int index, K arg) {
        int border = index;
        while (border < catalogSize && catalog[border].getKey() < arg)
            border++;
        while (border > 0 && catalog[border - 1].getKey() >= arg)
            border--;
        return border;
    }

    int getRightBorder(int index, K arg) {
        int border = index;
        while (border > 0 && catalog[border].getKey() > arg)
            border--;
        while (border < catalogSize && catalog[border + 1].getKey() == arg)
            border++;
        return border;
    }

public:
    Search() {
        mergeSort = new MergeSort<T>(new SortListener<T>());
        initialized = false;
    }

    Search(SearchMethod<T, I, K> *method) {
        mergeSort = new MergeSort<T>(new SortListener<T>());
        searchMethod = method;
        initialized = true;
    }


    void createCatalog(I *items, int size) {
        catalogSize = size;
        catalog = new T[catalogSize];
        for (int i = 0; i < catalogSize; i++) {
            T *item = &catalog[i];
            item->setKey(items[i].getKey()[0]);
            item->setItem(&items[i]);
        }
        catalog = mergeSort->sort(catalog, catalogSize);
    }

    T *getCatalog() {
        return catalog;
    }


    int *find(K arg) {
        int *borders = new int[2];
        borders[0] = -1;
        borders[1] = -1;
        if (!initialized) {
            cout << "Error: Need initialize search method" << endl;
            return borders;
        }
        int resIndex = searchMethod->onCallSearch(arg, catalog, catalogSize);

        if (catalog[resIndex].getKey() == arg) {
            borders[0] = getLeftBorder(resIndex, arg);
            borders[1] = getRightBorder(resIndex, arg);
        }
        return borders;
    }

    int *find(K arg1, K arg2) {
        int *borders = new int[2];
        borders[0] = -1;
        borders[1] = -1;
        if (!initialized) {
            cout << "Error: Need initialize search method" << endl;
            return borders;
        }
        //need sorted value args
        if (arg1 > arg2) {
            K tmp = arg1;
            arg1 = arg2;
            arg2 = tmp;
        }
        int resIndex1 = searchMethod->onCallSearch(arg1, catalog, catalogSize);
        int resIndex2 = searchMethod->onCallSearch(arg2, catalog, catalogSize);
        bool res1 = resIndex1 != -1;
        bool res2 = resIndex2 != -1;
        if (res1 || res2) {
            borders[0] = getLeftBorder(res1 ? resIndex1 : resIndex2, res1 ? arg1 : arg2);
            borders[1] = getRightBorder(res2 ? resIndex2 : resIndex1, res2 ? arg2 : arg1);
            if (borders[0] >= borders[1]) {
                borders[0] = -1;
                borders[1] = -1;
                return borders;
            }
        }
        return borders;
    }
};

#endif //TECH_PROG_LAB_2_2_1_SEARCH_H
