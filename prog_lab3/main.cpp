#include <iostream>
#include <fstream>
#include "access.h"

using namespace std;

void generateFile();

void readFile();

int main() {
    locale::global(locale(""));
    locale loc("");
    cout.imbue(loc);
    two();
    /*int choice = 0;
    while (1) {
        cout << "Сгенерировать файл - 1" << endl << "Прочитать файл - 2" << endl <<
        "Действие: ";
        cin >> choice;
        switch (choice) {
            case 1:
                generateFile();
                break;
            case 2:
                readFile();
                break;
            default:
                return 0;
        }
    }*/
    return 0;
}

void generateFile() {
    ofstream fout("/home/radiationx/ClionProjects.git/prog_lab3/file.bin", ios::out | ios::binary);
    int size = 10;
    double array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    fout.write((char *) &size, sizeof(size));
    fout.write((char *) &array, sizeof(array));
    fout.close();
    cout << endl << "Файл сгенерирован!" << endl << endl;
}

void readFile() {
    ifstream fin("/home/radiationx/ClionProjects.git/prog_lab3/file.bin", ios::in | ios::binary);
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
    cout << endl << "Разность сумм: " << sumArray[0] - sumArray[1] << endl << endl;
}