//
// Created by radiationx on 27.04.16.
//

#ifndef PROG_LAB3_ACCESS_H
#define PROG_LAB3_ACCESS_H

#include<locale>
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>

using namespace std;
struct data {
    string fio;
    int points[5];
    string phone;
};

void one() {
    //Generate file
    ofstream fout1("/home/radiationx/ClionProjects.git/prog_lab3/text.bin", ios::out | ios::binary);
    int size = 5;
    fout1.write((char *) &size, sizeof(int));
    data temp1[] =
            {
                    {"Familiya Imya Otchestvo1", {5, 10, 15, 20, 13}, "88005553535"},
                    {"Familiya Imya Otchestvo2", {100,100,100,100,100},   "88043535"},
                    {"Familiya Imya Otchestvo3", {100,100,100,100,100},   "43255553535"},
                    {"Familiya Imya Otchestvo4", {100,100,100,100,100},   "43255553535"},
                    {"Familiya Imya Otchestvo5", {5, 10, 15, 20, 13},   "43255553535"},
            };
    for (int i = 0; i < size; i++)
        fout1.write((char *) &temp1[i], sizeof(data));
    fout1.close();

    //Main
    ifstream fin("/home/radiationx/ClionProjects.git/prog_lab3/text.bin", ios::in | ios::binary);
    ofstream fout("/home/radiationx/ClionProjects.git/prog_lab3/out.bin", ios::out | ios::binary);
    int dataSize, middle = 0;
    fin.read((char *) &dataSize, sizeof(int));
    data *temp = new data[dataSize];
    for (int i = 0; i < dataSize; i++) {
        fin.read((char *) &temp[i], sizeof(data));
        for (int j = 0; j < 5; j++) {
            middle += temp[i].points[j];
        }
        middle /= 5;
        if (middle < 20) {
            fout.write((char *) &temp, sizeof(data));
            cout << temp[i].fio << endl;
        }
        middle = 0;
    }
    fin.close();
    fout.close();
}

void two() {
    //Generate file
    char initText[] = "jkdfh h  kjdfh j jf.";
    int initSize;
    ofstream fout("/home/radiationx/ClionProjects.git/prog_lab3/text2.bin", ios::out | ios::binary);
    initSize = sizeof(initText);
    fout.write((char*)&initSize, sizeof(initSize));
    fout.write((char *) &initText, initSize);
    fout.close();

    //Main
    ifstream fin("/home/radiationx/ClionProjects.git/prog_lab3/text2.bin", ios::in | ios::binary);
    fout.open("/home/radiationx/ClionProjects.git/prog_lab3/out2.bin", ios::out | ios::binary);

    int size = -1;
    fin.read((char*)&size, sizeof(size));

    char *text = new char[size];
    char *result = new char[size];

    for(int i = 0; i<size; i++)
        fin.read(&text[i], sizeof(char));

//    fin.read((char *) &text1, sizeof(string)*text.initSize());
//    fin.close();

    cout << endl << ": " << text<<endl;
    for (int i = 0, j = 0; i < size; i++) {
        if (text[i] != '\n' && text[i] != ' ' && text[i - 1] == ' ' && text[i + 1] == ' ') {
            //text.erase(i, 1);
            j--;
        } else if (!(text[i] == ' ' && (text[i + 1] == ' ' | text[i - 1] == ' '))) {
            result[j] = text[i];
            j++;
        }
    }
    cout << endl << ": " << result;
    fout.write((char *) &text, sizeof(text));
    fout.close();
}

#endif //PROG_LAB3_ACCESS_H
