#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
struct Item {
    string date = "";
    double rate = -1;
};
static string basePath = "/Users/radiationx/ClionProjects/ClionProjects/prog_lab_2_2/";
vector<Item> data;
static int TYPE_DATE = 0;
static int TYPE_RATE = 1;

Item parseLine(string line);

void parseData(string fileName);

void printData(bool printTotal);

void exportData(string fileName);

void remove(int index);

void add(Item item);

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
             << "2 - Print data" << endl
             << "3 - Print data and total value" << endl
             << "4 - Add item" << endl
             << "5 - Remove item by index" << endl
             << "6 - Export data" << endl
             << "0 - Exit" << endl << endl;
        cout << "Choice action: ";
        cin >> action;
        switch (action) {
            case 1: {
                string fileName;
                cout << "Enter file name: ";
                cin >> fileName;
                parseData(fileName);
                break;
            }
            case 2: {
                printData(false);
                break;
            }
            case 3: {
                printData(true);
                break;
            }
            case 4: {
                Item item = Item();
                cout << "Enter date: ";
                cin >> item.date;
                cout << "Enter rate: ";
                cin >> item.rate;
                add(item);
                break;
            }
            case 5: {
                int index = 0;
                cout << "Enter element index: ";
                cin >> index;
                remove(index);
                break;
            }
            case 6: {
                string fileName;
                cout << "Enter file name: ";
                cin >> fileName;
                exportData(fileName);
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

void parseData(string fileName) {
    data.clear();
    string path = basePath;
    ifstream inputStream(path.append(fileName), ios::in);
    if (inputStream.is_open()) {
        string temp;
        while (getline(inputStream, temp)) {
            Item item = parseLine(temp);
            if (item.rate != -1) {
                data.push_back(item);
            }
        }
    } else {
        cout << "Error: file not open" << endl;
    }
    inputStream.close();
}

void exportData(string fileName) {
    string path = basePath;
    ofstream outputStream(path.append(fileName), ios::out);
    string result = "";
    for (Item item:data) {
        result.append(item.date).append(" ").append(to_string(item.rate)).append("\n");
    }
    result.pop_back();
    outputStream << result;
    outputStream.close();
}

Item parseLine(string line) {
    int dataType = TYPE_DATE;
    Item item = Item();
    string value = "";
    for (int i = 0; i < line.size(); i++) {
        char c = line[i];
        if (c != ' ' && i + 1 < line.size()) {
            value += c;
        } else {
            if (dataType == TYPE_DATE) {
                item.date = value;
            } else if (dataType == TYPE_RATE) {
                item.rate = atof(value.c_str());
                break;
            }
            dataType = TYPE_RATE;
            value.clear();
        }
    }
    return item;
}

void printData(bool printTotal) {
    cout << "№\tDate\t\tRate" << endl;
    int i = 0;
    for (Item item:data) {
        cout << i << "\t" << item.date << "\t" << item.rate << endl;
        i++;
    }
    if (printTotal) {
        double max = 0;
        for (Item item:data) {
            if (item.rate > max)
                max = item.rate;
        }
        cout << "Maximum\t\t\t" << max << endl;
    }
}

void add(Item item) {
    data.push_back(item);
}

void remove(int index) {
    data.erase(data.begin() + index);
}
