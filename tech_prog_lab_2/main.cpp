#include <iostream>
#include <math.h>

#define L 5

using namespace std;
int N;

struct generalStructure {
    float key1;
    float key2[L];
    char key3;
};
struct floatStructure {
    float key;
    int index;
};
struct floatArrayStructure {
    float key[L];
    int index;
};
struct charStructure {
    char key;
    int index;
};

template<typename T>
void sortSimple(T *array, int count);

template<typename T>
void sortArray(T *array, int count);

template<typename T, typename A>
int searchArray(const T *array, const A arg);

template<typename T, typename A>
int searchSimple(const T *array, const A arg);


int main() {
    srand(time(NULL));

    cout << "Введите количество элементов: ";
    cin >> N;
    cout << endl;

    generalStructure *general = new generalStructure[N];
    floatStructure *catFloat = new floatStructure[N];
    floatArrayStructure *catFloatArray = new floatArrayStructure[N];
    charStructure *catChar = new charStructure[N];

    int n = 0;
    int *resultIndexes = new int[N];

    for (int i = 0; i < N; i++) {
        general[i].key1 = floor(((90) * ((float) rand() / RAND_MAX)) + 10);
        for (int j = 0; j < L; j++)
            general[i].key2[j] = floor(((90) * ((float) rand() / RAND_MAX)) + 10);
        general[i].key3 = 'a' + (char) (rand() % 26);

        catFloat[i].key = general[i].key1;
        catFloat[i].index = i;
        for (int j = 0; j < L; j++)
            catFloatArray[i].key[j] = general[i].key2[j];
        catFloatArray[i].index = i;
        catChar[i].key = general[i].key3;
        catChar[i].index = i;
    }

    for (int i = 0; i < N; i++) {
        cout << "{" << general[i].key1 << ", [";
        for (int j = 0; j < L; j++)
            cout << general[i].key2[j] << " ";
        cout << "], " << general[i].key3 << "}" << endl;
    }

    /*sortSimple(catFloat, N);
    sortArray(catFloatArray, N);
    sortSimple(catChar, N);*/

    cout << endl;
    float arg1;
    cout << "Поиск в поле float: ";
    cin >> arg1;
    int resultFloat = searchSimple(catFloat, arg1);
    if (resultFloat != -1) {
        resultIndexes[n] = resultFloat;
        n++;
    }


    cout << endl;
    int arg2[L];
    cout << "Поиск в поле int[" << L << "]: " << endl;
    for (int k = 0; k < L; k++) {
        cout << "Введите число " << k << ": ";
        cin >> arg2[k];
    }
    int resultFloatArray = searchArray(catFloatArray, arg2);
    if (resultFloatArray != -1) {
        if (resultFloatArray != resultFloat) {
            resultIndexes[n] = resultFloatArray;
            n++;
        }
    }

    cout << endl;
    char arg3;
    cout << "Поиск в поле char: ";
    cin >> arg3;
    int resultChar = searchSimple(catChar, arg3);
    if (resultChar != -1) {
        if (resultChar != resultFloat & resultChar != resultFloatArray) {
            resultIndexes[n] = resultChar;
            n++;
        }
    }

    cout << endl;
    if (n == 0)
        cout << "Нет совпадений." << endl;
    else {
        cout << "Совпадения (" << n << "): " << endl;
        for (int i = 0; i < n; i++) {
            cout << "{" << general[resultIndexes[i]].key1 << ", [";
            for (int j = 0; j < L; j++)
                cout << general[resultIndexes[i]].key2[j] << " ";
            cout << "], " << general[resultIndexes[i]].key3 << "}" << endl;
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

template<typename T>
void sortArray(T *array, int count) {
    int temp;
    for (int i = 0; i < count; i++)
        for (int j = 0; j < L; j++)
            for (int k = 0; k < L; k++)
                if (array[i].key[j] < array[i].key[k]) {
                    temp = array[i].key[j];
                    array[i].key[j] = array[i].key[k];
                    array[i].key[k] = temp;
                }
}

template<typename T, typename A>
int searchSimple(const T *array, const A arg) {
    int resIndex = -1,
            left = 1,
            right = N,
            middle;

    while (((right - left) != 1) || (array[resIndex].key == arg)) {
        middle = (left + right) / 2;
        if (arg == (int) array[middle].key) {
            resIndex = middle;
            break;
        }
        if (left > 0)
            left--;
        else if (right > 0)
            right--;
    }
    if (arg == (int) array[right].key)
        resIndex = right;
    if (arg == (int) array[left].key)
        resIndex = left;
    return resIndex;
}

template<typename T, typename A>
int searchArray(const T *array, const A arg) {
    int resIndex = -1,
            left = 1,
            right = N,
            middle;
    bool found = false;

    while (right > left) {
        middle = (right + left) / 2;
        for (int i = 0; i < L; i++) {
            for (int j = 0; j < L; j++) {
                if (arg[j] == array[middle].key[i]) {
                    resIndex = middle;
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        if (found)
            break;
        else if (left > 0)
            left--;
        else if (right > 0)
            right--;
        else break;
    }
    return resIndex;
}