#include <iostream>
#include <string>
#include <thread>
#include "parser/Parser.h"
#include "ui/ConsoleView.h"
#include <fstream>
#include <sstream>

using namespace std;
using namespace std::chrono;

string readFile(string fileName);

void initMenu();

static string basePath = "/Users/radiationx/ClionProjects/ClionProjects/course_work/";
Parser parser;
ConsoleView consoleView;
Element *rootDom = NULL;
Block *rootBlock = NULL;

int main() {
    initMenu();
    return 0;
}

string readFile(string fileName) {
    string result = "";
    string path = basePath;
    ifstream inputStream(path.append(fileName), ios::in);
    if (inputStream.is_open()) {
        string temp;
        while (getline(inputStream, temp)) {
            result.append(temp);
        }
        cout << "File successfully opened" << endl;
    } else {
        cout << "Error: file not open" << endl;
    }
    inputStream.close();
    return result;
}

void createData(string &htmlSource) {
    rootDom = parser.parse(htmlSource);
    cout << "DOM successfully created" << endl;
    rootBlock = consoleView.transformToBlock(rootDom, NULL);
    cout << "Tree of formatted rows was successfully created" << endl;
}

//todo сделать обработку ошибок
void initMenu() {
    cout << endl;
    int action = -1;
    for (; action != 0;) {
        cout << "---------- MENU ----------" << endl;
        cout << "1 - Open file" << endl
             << "2 - Edit available columns (current " << consoleView.getAvailColumns() << ")" << endl
             << "3 - Print text" << endl
             << "0 - Exit" << endl << endl;
        cout << "Choice action: ";
        while (!(cin >> action)) {
            cout << "Error. Retry choice action: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        switch (action) {
            case 1: {
                string fileName;
                cout << "Enter file name: ";
                while (!(cin >> fileName)) {
                    cout << "Error. Retry enter file name: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                string htmlSource = readFile(fileName);
                createData(htmlSource);
                break;
            }
            case 2: {
                int newAvailColumns = 0;
                cout << "Enter available columns: ";
                while (!(cin >> newAvailColumns)) {
                    cout << "Error. Retry enter available columns: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                consoleView.setAvailColumns(newAvailColumns);
                break;
            }
            case 3: {
                if (rootBlock == NULL) {
                    cout << "Error: Please open file first." << endl;
                    break;
                }
                consoleView.createBlockRows(*rootBlock);
                consoleView.printBlock(*rootBlock);
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

