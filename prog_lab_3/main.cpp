#include <iostream>
#include <fstream>
#include "access.h"

using namespace std;

void generateFile();

void readFile();
void readFile2();

int main() {
    locale::global(locale(""));
    locale loc("");
    cout.imbue(loc);
    int choice = 0;
    while (1) {
        cout << "Сгенерировать файл - 0" << endl << "Задание 1 - 1" << endl<< "Задание 2 - 2" <<endl << "Действие: ";
        cin >> choice;
        switch (choice) {
            case 0:
                generateFile();
                break;
            case 1:
                readFile();
                break;
            case 2:
                readFile2();
                break;
            default:
                return 0;
        }
    }
    return 0;
}

void generateFile() {
    cout<< endl <<"----------"<<endl;
    ofstream fout("/home/radiationx/ClionProjects.git/prog_lab_3/file.bin", ios::out | ios::binary);
    int size = 10;
    double array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    fout.write((char *) &size, sizeof(size));
    fout.write((char *) &array, sizeof(array));
    fout.close();
    cout <<"Файл сгенерирован!" << endl;
    cout<<"----------"<<endl<<endl;
}

void readFile() {
    cout<< endl <<"----------"<<endl;
    ifstream fin("/home/radiationx/ClionProjects.git/prog_lab_3/file.bin", ios::in | ios::binary);
    int size;
    fin.read((char *) &size, sizeof(size));
    double *array = new double[size];
    for (int i = 0; i < size; i++) {
        fin.read((char *) &array[i], sizeof(array));
    }
    fin.close();
    if (size < 3) {
        cout << "Ошибка: количество компонент < 3";
        return;
    }
    double sumArray[2] = {0, 0};
    for (int i = 0; i < 3; i++)
        sumArray[0] += array[i];
    for (int i = size - 1; i > size - 4; i--)
        sumArray[1] += array[i];
    cout << "Разность сумм: " << sumArray[0] - sumArray[1] << endl;
    cout<<"----------"<<endl<<endl;
}

void readFile2() {
    cout<< endl <<"----------"<<endl;
    ifstream fin("/home/radiationx/ClionProjects.git/prog_lab_3/file.bin", ios::in | ios::binary);
    int size;
    fin.read((char *) &size, sizeof(size));
    double *Array = new double[size];
    for (int i = 0; i < size; i++) {
        fin.read((char *) &Array[i], sizeof(double));
    }
    fin.close();
    double dataArray[3] = {0, 0, 0};

    int middle = size / 2;

    for (int i = 0; i < middle; i++)
        dataArray[0] += Array[i];

    for (int i = size - 1; i > size - middle - 1; i--)
        dataArray[1] *= Array[i];
    int j = 0;
    for (int i = 0; i < size; i++) {
        if (i % 3 == 0 && i != 0) {
            dataArray[2] += Array[i];
            j++;
        }
    }
    if (j != 0)
        dataArray[2] /=  j;
    cout << "Сумма первой половины: " << dataArray[0] << endl;
    cout << "Сумма второй половины: " << dataArray[1] << endl;
    cout << "Среднее арифметическое на местах, кратных 3: " << dataArray[2] << endl;
    cout<<"----------"<<endl<<endl;
}