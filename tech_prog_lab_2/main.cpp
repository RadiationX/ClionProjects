#include <iostream>
#include <math.h>

#define L 5

using namespace std;
int N;

struct generalStruct {
    float key;
    float keyArr[L];
    char keyChar[L];
};
struct floatStruct {
    float key;
    int index;
};
struct floatArrStruct {
    float keyArr[L];
    int index;
};
struct charArrStruct {
    char keyArr[L];
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

    generalStruct *general = new generalStruct[N];
    //Справочники
    floatStruct *catFloat = new floatStruct[N];
    floatArrStruct *catArrFloat = new floatArrStruct[N];
    charArrStruct *catArrChar = new charArrStruct[N];

    int n = 0;
    int *resultIndexes = new int[N];

    for (int i = 0; i < N; i++) {
        general[i].key = floor(((90) * ((float) rand() / RAND_MAX)) + 10);
        for (int j = 0; j < L; j++) {
            general[i].keyArr[j] = floor(((90) * ((float) rand() / RAND_MAX)) + 10);
            general[i].keyChar[j] = 'a' + (char) (rand() % 26);
        }
    }
    cout << "Неотсортированные данные:" << endl;
    for (int i = 0; i < N; i++) {
        cout << "{" << general[i].key << ", [";
        for (int j = 0; j < L; j++)
            cout << general[i].keyArr[j] << (j == L - 1 ? "" : " ");
        cout << "], [";
        for (int j = 0; j < L; j++)
            cout << general[i].keyChar[j] << (j == L - 1 ? "" : " ");
        cout << "]}" << endl;
    }
    cout << endl;

    //Заполнение справочников
    for (int i = 0; i < N; i++) {
        catFloat[i].key = general[i].key;
        for (int j = 0; j < L; j++) {
            catArrFloat[i].keyArr[j] = general[i].keyArr[j];
            catArrChar[i].keyArr[j] = general[i].keyChar[j];
        }
        catFloat[i].index = catArrFloat[i].index = catArrChar[i].index = i;
    }

    //Сортировка справочников
    sortSimple(catFloat, N);
    sortArray(catArrFloat, N);
    sortArray(catArrChar, N);

    //Основной массив теперь "отсортирован"
    for (int i = 0; i < N; i++) {
        general[i].key = catFloat[i].key;
        for (int j = 0; j < L; j++) {
            general[i].keyArr[j] = catArrFloat[i].keyArr[j];
            general[i].keyChar[j] = catArrChar[i].keyArr[j];
        }
        catFloat[i].index = catArrFloat[i].index = catArrChar[i].index = i;
    }

    cout << "Отсортированные данные:" << endl;
    for (int i = 0; i < N; i++) {
        cout << "{" << general[i].key << ", [";
        for (int j = 0; j < L; j++)
            cout << general[i].keyArr[j] << (j == L - 1 ? "" : " ");
        cout << "], [";
        for (int j = 0; j < L; j++)
            cout << general[i].keyChar[j] << (j == L - 1 ? "" : " ");
        cout << "]}" << endl;
    }


    cout << endl;
    float arg1;
    cout << "Поиск по float: ";
    cin >> arg1;
    int resultFloat = searchSimple(catFloat, arg1);
    if (resultFloat != -1) {
        resultIndexes[n] = resultFloat;
        n++;
    }

    cout << endl;
    float arg2[L];
    cout << "Поиск по int[" << L << "]: " << endl;
    for (int k = 0; k < L; k++) {
        cout << "Введите число " << k << ": ";
        cin >> arg2[k];
    }
    int resultFloatArray = searchArray(catArrFloat, arg2);
    if (resultFloatArray != -1) {
        if (resultFloatArray != resultFloat) {
            resultIndexes[n] = resultFloatArray;
            n++;
        }
    }

    cout << endl;
    char arg3[L];
    cout << "Поиск по char[" << L << "]: " << endl;
    for (int k = 0; k < L; k++) {
        cout << "Введите букву " << k << ": ";
        cin >> arg3[k];
    }
    int resultCharArray = searchArray(catArrChar, arg3);
    if (resultCharArray != -1) {
        if (resultCharArray != resultFloat & resultCharArray != resultFloatArray) {
            resultIndexes[n] = resultCharArray;
            n++;
        }
    }
    cout << endl;

    //cout<<resultFloat<<" : "<< resultFloatArray<<" : "<<resultCharArray<<endl;
    if (n == 0)
        cout << "Нет совпадений." << endl;
    else {
        cout << "Совпадения (" << n << "): " << endl;
        for (int i = 0; i < n; i++) {
            cout << "{" << general[resultIndexes[i]].key << ", [";
            for (int j = 0; j < L; j++)
                cout << general[resultIndexes[i]].keyArr[j] << (j == L - 1 ? "" : " ");
            cout << "], [";
            for (int j = 0; j < L; j++)
                cout << general[resultIndexes[i]].keyChar[j] << (j == L - 1 ? "" : " ");
            cout << "]}" << endl;
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
                if (array[i].keyArr[j] < array[i].keyArr[k]) {
                    temp = array[i].keyArr[j];
                    array[i].keyArr[j] = array[i].keyArr[k];
                    array[i].keyArr[k] = temp;
                }
}

template<typename T, typename A>
int searchSimple(const T *array, const A arg) {
    int resIndex = -1,
            left = 0,
            right = N,
            middle;

    while (left != right) {
        middle = (left + right) / 2;
        if (arg == array[middle].key) {
            resIndex = middle;
            break;
        }
        if (arg > array[middle].key)
            left = middle;
        else
            right = middle;
    }
    if (arg == array[right].key)
        resIndex = right;
    if (arg == array[left].key)
        resIndex = left;
    return resIndex;
}

template<typename T, typename A>
int searchArray(const T *array, const A arg) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < L; j++) {
            int resIndex = -1,
                    left = 0,
                    right = L,
                    middle;

            while (left < right) {
                middle = (left + right) / 2;
                //cout<<"compare "<<(arg[j] == array[i].keyArr[middle])<<" : "<<arg[j]<<" : "<<array[i].keyArr[middle]<<endl;
                if (arg[j] == array[i].keyArr[middle]) {
                    resIndex = i;
                    break;
                }
                //cout<<"info: "<<(arg[j] > array[i].keyArr[middle])<<" : "<<middle<<" : "<<left<<" : "<<right<<endl;
                if (arg[j] > array[i].keyArr[middle]) {
                    if (middle - left == 0) break;
                    left = middle;
                } else {
                    if (right - middle == 0) break;
                    right = middle;
                }
            }
            if (arg[j] == array[i].keyArr[right] || arg[j] == array[i].keyArr[left])
                resIndex = i;

            if (resIndex != -1)
                return resIndex;
        }
    }
    return -1;
}