#include <iostream>
#include <fstream>

using namespace std;
struct data {
    string fio;
    int points[5];
    string phone;
};

void one();

void two();

void generateFile() {
    ofstream fout("/home/radiationx/ClionProjects.git/prog_lab3/file.bin", ios::out | ios::binary);
    int size = 2;
    double array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    fout.write((char *) &size, sizeof(size));
    fout.write((char *) &array, sizeof(array));
    fout.close();
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
    cout << "Разность сумм: " << sumArray[0] - sumArray[1];
}

int main() {
    locale::global(locale(""));
    locale loc("");
    cout.imbue(loc);
    generateFile();
    readFile();
    return 0;
}

void one() {
    ifstream fin("/home/radiationx/ClionProjects.git/prog_lab3/text.txt", ios::in);
    ofstream fout("/home/radiationx/ClionProjects.git/prog_lab3/out.txt", ios::out);
    string text, outText, temp;
    char buff;
    int dataSize = 0, colon = 0;
    data *datas;
    string::size_type sz;
    while (fin.get(buff)) {
        text += buff;
        if (buff == '\n')
            dataSize++;
    }
    fin.close();

    datas = new data[dataSize + 1];
    dataSize = 0;

    for (int i = 0; i < text.size(); i++) {
        if (text[i] == ':') {
            colon++;
            temp = "";
            continue;
        }
        if (text[i] == '\n') {
            dataSize++;
            colon = 0;
            continue;
        }

        if (colon == 0) {
            datas[dataSize].fio += text[i];
        } else if (colon > 0 && colon < 6) {
            temp += text[i];
            datas[dataSize].points[colon - 1] = stoi(temp, &sz);
        } else {
            datas[dataSize].phone += text[i];
        }
    }

    int middle = 0;
    for (int i = 0; i < dataSize + 1; i++) {
        for (int j = 0; j < 5; j++) {
            middle += datas[i].points[j];
        }
        middle /= 5;
        cout << middle << endl;
        if (middle < 20) {
            if (i != 0)
                outText.append("\n");
            outText.append(datas[i].fio).append(":");
            for (int j = 0; j < 5; j++)
                outText.append(to_string(datas[i].points[j])).append(":");
            outText.append(datas[i].phone);

        }
        middle = 0;
    }
    fout << outText;
    fout.close();
}

void two() {
    ifstream fin("/home/radiationx/ClionProjects.git/prog_lab3/text2.txt", ios::in);
    ofstream fout("/home/radiationx/ClionProjects.git/prog_lab3/out2.txt", ios::out);
    string text, result;
    char buff;
    while (fin.get(buff))
        text += buff;
    fin.close();

    for (int i = 0; i < text.size(); i++) {
        if (text[i] != '\n' && text[i] != ' ' && text[i - 1] == ' ' && text[i + 1] == ' ') {
            text.erase(i, 1);
        } else if (!(text[i] == ' ' && (text[i + 1] == ' ' | text[i - 1] == ' '))) {
            result += text[i];
        }
    }
    fout << result;
    fout.close();
}