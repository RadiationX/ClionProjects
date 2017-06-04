#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include "parser/Document.h"
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


unsigned long *suka4ka(string &S, int *length) {
    for (int i = 0; i < S.length(); i++) {
        if (isspace(S[i])) {
            *length = *length + 1;
        }
    }
    unsigned long *result = new unsigned long[*length];

    int j = 0;
    for (int i = 0; i < S.length(); i++) {
        if (isspace(S[i])) {
            result[j] = i;
            j++;
        }
    }
    return result;
}

int columns = 35;
const int ALIGN_LEFT = 0;
const int ALIGN_RIGHT = 1;
const int ALIGN_CENTER = 2;
const int ALIGN_JUSTIFY = 3;

void printString(int indent, int align, string s) {
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
        cout << "AAAAAAAAAAAAAAAAAAA# " << start << " : " << len << endl;
        if (start == len)
            break;
        if (i == 0) {
            for (int j = 0; j < indent; j++) {
                result.append(" ");
            }
            shifted += indent;
        } else if (i == 1) {
            shifted -= indent;
        }

        toPrint = (unsigned long) (columns + shifted) /*- 1*/;
        toPrint = (unsigned long) min(columns, (const int &) toPrint);
        cout << "SSSSA  USAIODASIOUDPOAS " << toPrint << " : " << start << " : " << (start + toPrint) << " : "
             << len - 1
             << endl;
        toPrint = start + toPrint > len - 1 ? len - start : toPrint;

        unsigned long tailIndex = start + toPrint - shifted;

        cout << "CHECK " << tailIndex << ": " << s[tailIndex] << " AND " << s[tailIndex + 1] << " AND "
             << s[tailIndex - 1] << endl;

        if ((tailIndex != len) && !isspace(s[tailIndex]) &&
            (!isspace(s[tailIndex + 1]) || !isspace(s[tailIndex - 1]))) {
            cout << "CHECK3/4: " << start << " : " << tailIndex << endl;
            cout << "CHECK '";
            while (!(isspace(s[tailIndex]))) {
                cout << s[tailIndex];
                if (tailIndex == start) {
                    break;
                }
                tailIndex--;
                shifted++;
            }
            cout << "'" << endl;
        }


        while (isspace(s[start])) {
            start++;
        }

        cout << "PISYA: " << s[tailIndex - 1] << endl;
        while (isspace(s[tailIndex - 1])) {
            tailIndex--;
        }


        toPrint = tailIndex - start;
        cout << "FINAL: " << start << "+" << toPrint << " : " << tailIndex << " : " << shifted << endl;
        lastShifted = shifted;

        //cout << s.substr(start, toPrint) << endl;
        string to_print = s.substr(start, toPrint);
        cout << "TO_PRINT '" << to_print << "'" << endl;
        if (align == ALIGN_RIGHT) {
            unsigned long length = to_print.length();
            if (i == 0) {
                length += indent;
            }
            for (unsigned long j = 0; j < (columns - length); j++) {
                result.append(" ");
            }
        }
        if (align == ALIGN_JUSTIFY) {
            int indicesLength = 0;
            unsigned long *spaceIndices = suka4ka(to_print, &indicesLength);

            while ((i == 0 ? to_print.length() + indent : to_print.length()) < columns) {
                for (unsigned long si = 0; si < indicesLength; si++) {
                    if ((i == 0 ? to_print.length() + indent : to_print.length()) >= columns) {
                        break;
                    }
                    to_print.insert(spaceIndices[si], " ");
                    for (unsigned long sj = si; sj < indicesLength; sj++) {
                        spaceIndices[sj]++;
                    }
                }
            }
        }
        if (align == ALIGN_CENTER) {
            unsigned long length = i == 0 ? to_print.length() + indent : to_print.length();

            unsigned long delta = columns - length;
            unsigned long left = delta / 2;
            unsigned long right = delta - left;
            to_print.insert(0, left, ' ');
            to_print.insert(to_print.length(), right, ' ');

            cout << "ALIGN_CENTER " << length << " : " << columns << " : " << (35 - 27) << endl;
        }
        result.append(to_print);


        if (align == ALIGN_LEFT) {
            unsigned long length = to_print.length();
            if (i == 0) {
                length += indent;
            }
            for (unsigned long j = 0; j < (columns - length); j++) {
                result.append(" ");
            }
        }

        cout << "TO_PRINT FINAL'" << to_print << "'" << endl;
        result.append("\n");
        toPrint += start;
        i++;
        if (i > 15) {
            cout << "ERROR VIDIMO" << endl;
            break;
        }
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
    string suka = "";
    suka = readFile("test3.txt");
    printString(4, ALIGN_CENTER, suka);
    int length = 0;
    return 0;
}