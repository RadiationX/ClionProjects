#include <iostream>
#include <math.h>

#define L 5

using namespace std;
int N;

struct generalCat {
    float key;
    float keyArr[L];
    char keyChar[L];
};
struct floatCat {
    float key;
    int index;
};
struct floatArrCat {
    float keyArr[L];
    int index;
};
struct charArrCat {
    char keyArr[L];
    int index;
};

template<typename T>
void sortSimple(T *array, int count);

template<typename T, typename A>
int *searchArray(const T *array, const A arg, int &resultSize);

template<typename T, typename A>
int *searchSimple(const T *array, const A arg, int &resultSize);


int main() {
    srand(time(NULL));

    cout << "Enter number of elements: ";
    cin >> N;

    generalCat *general = new generalCat[N];

    //Catalogs
    floatCat *catFloat = new floatCat[N];
    floatArrCat *catArrFloat = new floatArrCat[N];
    charArrCat *catArrChar = new charArrCat[N];

    for (int i = 0; i < N; i++) {
        catFloat[i].key = general[i].key = floor(((90) * ((float) rand() / RAND_MAX)) + 10);
        for (int j = 0; j < L; j++) {
            catArrFloat[i].keyArr[j] = general[i].keyArr[j] = floor(((90) * ((float) rand() / RAND_MAX)) + 10);
            catArrChar[i].keyArr[j] = general[i].keyChar[j] = 'a' + (char) (rand() % 26);
        }
        catFloat[i].index = catArrFloat[i].index = catArrChar[i].index = i;
    }

    cout << endl << "Initial data:" << endl;
    for (int i = 0; i < N; i++) {
        cout << "{" << general[i].key << ", [";
        for (int j = 0; j < L; j++)
            cout << general[i].keyArr[j] << (j == L - 1 ? "" : " ");
        cout << "], [";
        for (int j = 0; j < L; j++)
            cout << general[i].keyChar[j] << (j == L - 1 ? "" : " ");
        cout << "]}" << endl;
    }

    sortSimple(catFloat, N);

    //SEARCH
    float argFloat;
    cout << endl << "Search by field float: ";
    cin >> argFloat;
    int sizeResFloat = 0;
    int *resFloat = searchSimple(catFloat, argFloat, sizeResFloat);


    float argFloarArr[L];
    cout << endl << "Search by field int[" << L << "]: " << endl;
    for (int k = 0; k < L; k++) {
        cout << "Enter number " << k << ": ";
        cin >> argFloarArr[k];
    }
    int sizeResFloatArr = 0;
    int *resFloatArr = searchArray(catArrFloat, argFloarArr, sizeResFloatArr);


    char argCharArr[L];
    cout << endl << "Search by field char[" << L << "]: " << endl;
    for (int k = 0; k < L; k++) {
        cout << "Enter symbol " << k << ": ";
        cin >> argCharArr[k];
    }
    int sizeResCharArr = 0;
    int *resCharArr = searchArray(catArrChar, argCharArr, sizeResCharArr);


    //Print result
    cout << endl;
    if (sizeResFloat == 0 | sizeResFloatArr == 0 | sizeResCharArr == 0) {
        cout << "Nothing found" << endl;
    } else {
        int n = 0;
        int *resultIndexes = new int[N];

        for (int i = 0; i < sizeResFloat; i++) {
            for (int j = 0; j < sizeResFloatArr; j++) {
                for (int k = 0; k < sizeResCharArr; k++) {
                    if (resFloat[i] == resFloatArr[j] && resFloat[i] == resCharArr[k]) {
                        resultIndexes[n] = resFloat[i];
                        n++;
                    }
                }
            }
        }

        if (n != 0) {
            cout << "Founded elements ("<<n<<"):" << endl;
            for (int i = 0; i < n; i++) {
                cout << "{" << general[resultIndexes[i]].key << ", [";
                for (int j = 0; j < L; j++)
                    cout << general[resultIndexes[i]].keyArr[j] << (j == L - 1 ? "" : " ");
                cout << "], [";
                for (int j = 0; j < L; j++)
                    cout << general[resultIndexes[i]].keyChar[j] << (j == L - 1 ? "" : " ");
                cout << "]}" << endl;
            }
        } else {
            cout << "Nothing found" << endl;
        }
    }
    return 0;
}

template<typename T>
void sortSimple(T *array, int count) {
    T temp;
    for (int i = 0; i < count; ++i)
        for (int j = i + 1; j < count; ++j)
            if (array[j].key < array[i].key) {
                temp = array[j];
                array[j] = array[i];
                array[i] = temp;
            }
}

template<typename T, typename A>
int *searchSimple(const T *array, const A arg, int &resultSize) {
    int resIndex = -1,
            left = 0,
            right = N,
            middle;

    resultSize = 0;
    int *result = new int[N];
    while (left != right) {
        middle = (left + right) / 2;
        if (arg == array[middle].key) {
            resIndex = array[middle].index;
            result[resultSize] = resIndex;
            resultSize++;
            break;
        }
        if (arg > array[middle].key)
            left = middle;
        else
            right = middle;
    }
    if (resIndex != -1) {
        //Find nearest
        while (arg == array[resIndex + 1].key && resIndex < right) {
            result[resultSize] = array[resIndex + 1].index;
            resultSize++;
            resIndex++;
        }
        resIndex = result[0];
        while (arg == array[resIndex - 1].key && resIndex >= left) {
            result[resultSize] = array[resIndex - 1].index;
            resultSize++;
            resIndex--;
        }
    } else {
        if (arg == array[right].key)
            resIndex = array[right].index;
        if (arg == array[left].key)
            resIndex = array[left].index;
        result[resultSize] = resIndex;
        resultSize++;
    }
    return result;
}

template<typename T, typename A>
int *searchArray(const T *array, const A arg, int &resultSize) {
    int *result = new int[N];
    resultSize = 0;
    bool found = true;
    for (int i = 0; i < N; i++) {
        found = true;
        for (int j = 0; j < L; j++) {
            if (array[i].keyArr[j] != arg[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            result[resultSize] = i;
            resultSize++;
        }
    }
    return result;
}