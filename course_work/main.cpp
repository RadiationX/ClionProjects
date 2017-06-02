#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include "parser/Document.h"
#include <fstream>
#include "Regex-Matcher-master/reg_exp.h"

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

std::vector<std::string> split(const std::string &s) {
    std::vector<std::string> v;

    const auto end = s.end();
    auto to = s.begin();
    decltype(to) from;

    while ((from = std::find_if(to, end, [](char c) { return !std::isspace(c); })) != end) {
        to = std::find_if(from, end, [](char c) { return std::isspace(c); });
        v.emplace_back(from, to);
    }

    return v;
}

int columns = 35;

void printString(int indent, string s) {
    unsigned long len = s.length();
    cout << "PRINT: " << s << endl << endl;
    int shifted = 0;
    unsigned long start = 0;
    unsigned long toPrint = 0;
    if (indent > columns) {
        indent = columns;
    }
    //indent = 0;

    string result = "";
    int lastShifted = 0;
    unsigned long iterations = (len + shifted) / columns;
    int i = 0;
    while (start != len) {
        //cout << "ITERATIONS " << i << " in " << (iterations) << endl;
        shifted -= lastShifted;

        start = toPrint;

        if (start == len)
            break;

        if (i == 0) {
            for (int j = 0; j < indent; j++) {
                //cout << " ";
                result.append(" ");
            }
            shifted += indent;
        } else if (i == 1) {
            shifted -= indent;
        }
        if (s[start] == ' ') {
            start++;
        }

        toPrint = (unsigned long) (columns + shifted) - 1;
        toPrint = (unsigned long) min(columns, (const int &) toPrint);
        toPrint = start + toPrint > len - 1 ? len - start - 1 : toPrint;
        unsigned long tailIndex = start + toPrint - shifted;

        cout << "CHECK " << tailIndex << ": " << s[tailIndex] << " AND " << s[tailIndex + 1] << " AND "
             << s[tailIndex - 1] << endl;

        if (!isspace(s[tailIndex]) && (!isspace(s[tailIndex + 1]) || !isspace(s[tailIndex - 1]))) {
            cout << "CHECK ";
            bool found = true;
            while (!(ispunct(s[tailIndex]) || isspace(s[tailIndex]))) {
                cout << s[tailIndex];
                if (tailIndex == start) {
                    found = false;
                    break;
                }
                tailIndex--;
                shifted++;
            }
            if (found) {
                tailIndex++;
                shifted--;
                if (ispunct(s[tailIndex])) {
                    tailIndex++;
                    shifted--;
                }
            }
            cout << endl;
        }

        toPrint = tailIndex - start;
        cout << "FINAL: " << start << "+" << toPrint << " : " << tailIndex << " : " << shifted << endl;
        lastShifted = shifted;

        //cout << s.substr(start, toPrint) << endl;
        result.append(s.substr(start, toPrint)).append("\n");
        toPrint += start;
        i++;
    }
    for (int j = 0; j < columns; j++) {
        cout << "_";
    }
    cout << "|" << endl;
    cout << result;
}

int main() {
    /*string htmlSource = readFile("test2.txt");
    Document *document = new Document();
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    cout << "Start parsing" << endl;
    //usleep(750 * 1000);

    //cout<<htmlSource;
    document->parse(htmlSource);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(t2 - t1).count() / 1000;
    cout << endl << "End parsing" << endl;
    cout << "Parsing time: " << duration << "ms" << endl;*/
    //cout << document->html() << endl;
    /*string suka = "";
    suka = readFile("test3.txt");
    printString(4, suka);*/

    int ssafd = 10;
    const char *text = "suka6667pisya";
    const char *piska = regex_search("pi(s)ya", text, &ssafd);

    cout <<ssafd << " : " << text << " : " << piska << endl;

    return 0;
}