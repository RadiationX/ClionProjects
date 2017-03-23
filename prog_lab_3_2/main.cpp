#include <iostream>
#include <fstream>
#include "Queue.h"

using namespace std;

struct Item {
    string date = "";
    double rate = -1;
};
static string basePath = "/Users/radiationx/ClionProjects/ClionProjects/prog_lab_3_2/";
Queue<Item> data(1000);

void importData(string fileName);

void exportData(string fileName);

void printData();

void initMenu();

int main() {
    initMenu();
    return 0;
}

void initMenu() {
    cout << endl;
    int action = -1;
    for (; action != 0;) {
        cout << "---------- MENU ----------" << endl;
        cout << "1 - Read file" << endl
             << "2 - Add item" << endl
             << "3 - Remove" << endl
             << "4 - Clear" << endl
             << "5 - Print data" << endl
             << "6 - Export data" << endl
             << "7 - Generate data" << endl
             << "0 - Exit" << endl << endl;
        cout << "Choice action: ";
        cin >> action;
        switch (action) {
            case 1: {
                string fileName;
                cout << "Enter file name: ";
                cin >> fileName;
                importData(fileName);
                break;
            }
            case 2: {
                Item item = Item();
                cout << "Enter date: ";
                cin >> item.date;
                cout << "Enter rate: ";
                cin >> item.rate;
                data.push(item);
                break;
            }
            case 3: {
                data.pop();
                break;
            }
            case 4: {
                data.clear();
                break;
            }
            case 5: {
                printData();
                break;
            }
            case 6: {
                string fileName;
                cout << "Enter file name: ";
                cin >> fileName;
                exportData(fileName);
                break;
            }
            case 7: {
                for (int i = 0; i < 7; i++) {
                    Item item = Item();
                    item.date = to_string((i + 1) * 11111111);
                    item.rate = (i + 10) + (i % 7 * 0.1f);
                    data.push(item);
                }
                break;
            }
            case 0:
                return;
            default:
                continue;
        }
        cout << endl;
    }
}

void importData(string fileName) {
    string path = basePath;
    ifstream inputStream(path.append(fileName), ios::in | ios::binary);
    if (inputStream.is_open()) {
        int dataSize;
        inputStream.read((char *) &dataSize, sizeof(int));
        for (int i = 0; i < dataSize; i++) {
            int charSize;
            inputStream.read((char *) &charSize, sizeof(int));

            Item item = Item();
            char *rateField = new char[charSize + 1];
            inputStream.read(rateField, charSize);
            rateField[charSize] = '\0';
            item.date = rateField;

            inputStream.read((char *) &item.rate, sizeof(double));
            data.push(item);
        }
    } else {
        cout << "Error: file not open" << endl;
    }
    inputStream.close();
}

void exportData(string fileName) {
    string path = basePath;
    ofstream outputStream(path.append(fileName), ios::out | ios::binary);
    int dataSize = data.size();
    outputStream.write((char *) &dataSize, sizeof(int));
    for (int i = data.frontIndex(); i < data.backIndex(); i++) {
        Item item = data.get(i);
        int charSize = (int) item.date.size();
        outputStream.write((char *) &charSize, sizeof(int));
        outputStream.write(item.date.c_str(), charSize);
        outputStream.write((char *) &item.rate, sizeof(double));
    }
    outputStream.close();
}

void printData() {
    cout << "№\tDate\t\tRate" << endl;
    for (int i = data.frontIndex(); i < data.backIndex(); i++) {
        Item item = data.get(i);
        cout << i << "\t" << item.date << "\t" << item.rate << endl;
    }
    cout<<"Size: "<<data.size()<<endl;
}