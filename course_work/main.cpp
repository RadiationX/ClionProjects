#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include "parser/Parser.h"
#include "ui/ConsoleView.h"
#include <fstream>
#include <sstream>

using namespace std;
using namespace std::chrono;

static string basePath = "/Users/radiationx/ClionProjects/ClionProjects/course_work/";

string readFile(string fileName) {
    string result = "";
    string path = basePath;
    ifstream inputStream(path.append(fileName), ios::in);
    if (inputStream.is_open()) {
        string temp;
        while (getline(inputStream, temp)) {
            result.append(temp);
        }
    } else {
        cout << "Error: file not open" << endl;
    }
    inputStream.close();
    return result;
}


void printRows(vector<string> rows) {
    for (string row:rows) {
        cout << row;
        cout << endl;
    }
}

int main() {
    string htmlSource = readFile("test4.html");
    Parser *parser = new Parser();
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    cout << "Start parsing" << endl;
    //usleep(750 * 1000);

    //cout<<htmlSource;
    Element *root = parser->parse(htmlSource);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(t2 - t1).count() / 1000;
    cout << endl << "End parsing" << endl;
    cout << "Parsing time: " << duration << "ms" << endl;
    //cout << root->html() << endl;

    ConsoleView consoleView;
    Block * block = consoleView.transformToBlock(root, NULL);
    block->availColumns = 60;
    consoleView.printBlockRecurse(*block);
    printRows(block->rows);

    return 0;
}