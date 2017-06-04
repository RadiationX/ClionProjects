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

unsigned long *getSpaceIndices(string &S, int *length) {
    for (int i = 0; i < S.length(); i++) {
        if (isspace(S[i])) {
            *length = *length + 1;
        }
    }
    unsigned long *result = new unsigned long[*length];

    int j = 0;
    for (unsigned long i = 0; i < S.length(); i++) {
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

void alignBase(int align, string &rowString, bool isIndented, int indent) {
    unsigned long length = columns - rowString.length();
    if (isIndented)
        length -= indent;
    unsigned long insertIndex = align == ALIGN_RIGHT ? 0 : rowString.length();
    rowString.insert(insertIndex, length, ' ');
}

void alignCenter(string &rowString, bool isIndented, int indent) {
    unsigned long delta = columns - rowString.length();
    if (isIndented)
        delta -= indent;
    unsigned long left = delta / 2;
    unsigned long right = delta - left;
    rowString.insert(0, left, ' ');
    rowString.insert(rowString.length(), right, ' ');
}

void alignJustify(string &rowString, bool isIndented, int indent) {
    int indicesLength = 0;
    unsigned long *spaceIndices = getSpaceIndices(rowString, &indicesLength);

    while ((isIndented ? rowString.length() + indent : rowString.length()) < columns) {
        for (unsigned long si = 0; si < indicesLength; si++) {
            if ((isIndented ? rowString.length() + indent : rowString.length()) >= columns) {
                break;
            }
            rowString.insert(spaceIndices[si], 1, ' ');
            for (unsigned long sj = si; sj < indicesLength; sj++) {
                spaceIndices[sj]++;
            }
        }
    }
}


void printString(int indent, int align, string s) {
    cout << "PRINT: " << s << endl << endl;
    if (indent > columns) {
        indent = columns;
    }

    string result = "";
    int lastOffset = 0;
    int rowsCount = 0;
    int offset = 0;
    unsigned long startIndex = 0;
    unsigned long len = s.length();
    while (startIndex != len) {
        offset -= lastOffset;

        //Отступ первой строки
        bool isIndented = indent > 0 && rowsCount == 0;
        if (isIndented) {
            for (int j = 0; j < indent; j++) {
                result.append(" ");
            }
            offset += indent;
        } else if (rowsCount == 1) {
            offset -= indent;
        }

        unsigned long lengthToPrint = (unsigned long) (columns + offset);
        lengthToPrint = (unsigned long) min(columns, (const int &) lengthToPrint);
        lengthToPrint = startIndex + lengthToPrint > len - 1 ? len - startIndex : lengthToPrint;

        unsigned long tailIndex = startIndex + lengthToPrint - offset;

        //Правильно пределяем индексы для правильного переноса строк
        if ((tailIndex != len) && !isspace(s[tailIndex]) &&
            (!isspace(s[tailIndex + 1]) || !isspace(s[tailIndex - 1]))) {
            while (!(isspace(s[tailIndex]))) {
                if (tailIndex == startIndex) {
                    break;
                }
                tailIndex--;
                offset++;
            }
        }

        //"Убираем" пробелы вначале
        while (isspace(s[startIndex])) {
            startIndex++;
        }

        //"Убираем" пробелы вконце
        while (isspace(s[tailIndex - 1])) {
            tailIndex--;
        }

        //Находим длину строки для вывода
        lengthToPrint = tailIndex - startIndex;
        lastOffset = offset;

        //Финальная обработка строки
        string rowString = s.substr(startIndex, lengthToPrint);
        switch (align) {
            case ALIGN_JUSTIFY:
                alignJustify(rowString, isIndented, indent);
                break;
            case ALIGN_CENTER:
                alignCenter(rowString, isIndented, indent);
                break;
            case ALIGN_LEFT:;
            case ALIGN_RIGHT:;
            default:
                alignBase(align, rowString, isIndented, indent);
                break;
        }

        result.append(rowString).append("\n");

        //Смещаем индексы вперед по строке
        lengthToPrint += startIndex;
        startIndex = lengthToPrint;

        rowsCount++;
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
    printString(4, ALIGN_RIGHT, suka);
    int length = 0;
    return 0;
}