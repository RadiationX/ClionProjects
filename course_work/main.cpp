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

//int availColumns = 35;
const int ALIGN_LEFT = 0;
const int ALIGN_RIGHT = 1;
const int ALIGN_CENTER = 2;
const int ALIGN_JUSTIFY = 3;

void alignBase(int align, string &rowString, int availColumns, bool isIndented, int indent) {
    unsigned long length = availColumns - rowString.length();
    /*if (isIndented)
        length += indent;*/
    unsigned long insertIndex = align == ALIGN_RIGHT ? 0 : rowString.length();
    rowString.insert(insertIndex, length, ' ');
}

void alignCenter(string &rowString, int availColumns, bool isIndented, int indent) {
    unsigned long delta = availColumns - rowString.length();
    /*if (isIndented)
        delta -= indent;*/
    unsigned long left = delta / 2;
    unsigned long right = delta - left;
    rowString.insert(0, left, ' ');
    rowString.insert(rowString.length(), right, ' ');
}

void alignJustify(string &rowString, int availColumns, bool isIndented, int indent) {
    int indicesLength = 0;
    unsigned long *spaceIndices = getSpaceIndices(rowString, &indicesLength);

    if (indicesLength == 0) {
        rowString.insert(rowString.length(), availColumns - rowString.length(), ' ');
    } else {
        while (rowString.length() < availColumns) {
            for (unsigned long si = 0; si < indicesLength; si++) {
                if (rowString.length() >= availColumns) {
                    break;
                }
                rowString.insert(spaceIndices[si], 1, ' ');
                for (unsigned long sj = si; sj < indicesLength; sj++) {
                    spaceIndices[sj]++;
                }
            }
        }
    }
}


vector<string> printString(string s, int availColumns, int align, int indent) {
    cout << "PRINT: " << s << endl << endl;
    if (indent > availColumns) {
        indent = availColumns;
    }

    vector<string> result;
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
            offset += indent;
        } else if (rowsCount == 1) {
            offset -= indent;
        }

        unsigned long lengthToPrint = (unsigned long) (availColumns + offset);
        lengthToPrint = (unsigned long) min(availColumns, (const int &) lengthToPrint);
        lengthToPrint = startIndex + lengthToPrint > len - 1 ? len - startIndex : lengthToPrint;

        unsigned long tailIndex = startIndex + lengthToPrint - offset;

        //Правильно определяем индексы для правильного переноса строк
        if ((tailIndex != len) && !isspace(s[tailIndex]) &&
            (!isspace(s[tailIndex + 1]) || !isspace(s[tailIndex - 1]))) {
            while (!(isspace(s[tailIndex]))) {
                if (tailIndex == startIndex)
                    break;
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
        if (isIndented) {
            rowString.insert(0, (unsigned long) indent, ' ');
        }
        switch (align) {
            case ALIGN_JUSTIFY:
                alignJustify(rowString, availColumns, isIndented, indent);
                break;
            case ALIGN_CENTER:
                alignCenter(rowString, availColumns, isIndented, indent);
                break;
            case ALIGN_LEFT:;
            case ALIGN_RIGHT:;
            default:
                alignBase(align, rowString, availColumns, isIndented, indent);
                break;
        }

        result.push_back(rowString);

        //Смещаем индексы вперед по строке
        lengthToPrint += startIndex;
        startIndex = lengthToPrint;

        rowsCount++;
    }
    return result;
}

struct Padding {
    int base = 0;
    int left = 0;
    int top = 0;
    int right = 0;
    int bottom = 0;

    int getLeft() {
        return left == 0 ? base : left;
    }

    int getTop() {
        return top == 0 ? base : top;
    }

    int getRight() {
        return right == 0 ? base : right;
    }

    int getBottom() {
        return bottom == 0 ? base : bottom;
    }
};

struct Margin {
    int base = 0;
    int left = 0;
    int top = 0;
    int right = 0;
    int bottom = 0;

    int getLeft() {
        return left == 0 ? base : left;
    }

    int getTop() {
        return top == 0 ? base : top;
    }

    int getRight() {
        return right == 0 ? base : right;
    }

    int getBottom() {
        return bottom == 0 ? base : bottom;
    }
};

struct Border {
    bool base = false;
    bool left = false;
    bool top = false;
    bool right = false;
    bool bottom = false;

    bool getLeft() {
        return !left ? base : left;
    }

    bool getTop() {
        return !top ? base : top;
    }

    bool getRight() {
        return !right ? base : right;
    }

    bool getBottom() {
        return !bottom ? base : bottom;
    }
};

void printBlock(string &text, int availColumns, Padding padding, Margin margin, Border border) {
    int contentColumns = availColumns - (margin.getLeft() + padding.getRight() + padding.getLeft() + margin.getRight() +
                                         border.getLeft() + border.getRight());
    cout << "INSET COLUMNS " << contentColumns << endl;
    vector<string> rows = printString(text, contentColumns, ALIGN_JUSTIFY, 4);

    int insetColumns = contentColumns + (padding.getLeft() + padding.getRight());
    int boxColumns = insetColumns + (border.getLeft() + border.getRight());
    //margins string
    string ml(margin.getLeft(), ' ');
    string mr(margin.getRight(), ' ');
    string mt(availColumns, ' ');
    string mb(availColumns, ' ');


    //paddings string
    string pl(padding.getLeft(), ' ');
    string pr(padding.getRight(), ' ');
    string pt(insetColumns, ' ');
    string pb(insetColumns, ' ');

    //borders string
    string bl(border.getLeft(), '|');
    string br(border.getRight(), '|');
    string bt(insetColumns, '-');
    string bb(insetColumns, '-');

    for (int i = 0; i < margin.getTop(); i++) {
        cout << mt << endl;
    }

    if (border.getTop()) {
        cout << ml;

        cout << " ";
        cout << bt;
        cout << " ";

        cout << mr;

        cout << endl;
    }

    if (padding.getTop()) {

    }
    for (int i = 0; i < padding.getTop(); i++) {
        cout << ml;
        cout << bl;

        cout << pt;

        cout << br;
        cout << mr;

        cout << endl;
    }


    for (string row:rows) {
        cout << ml;
        cout << bl;
        cout << pl;

        cout << row;

        cout << pr;
        cout << br;
        cout << mr;

        cout << endl;
    }


    for (int i = 0; i < padding.getBottom(); i++) {
        cout << ml;
        cout << bl;

        cout << pb;

        cout << br;
        cout << mr;

        cout << endl;
    }
    if (border.getBottom()) {
        cout << ml;

        cout << " ";
        cout << bb;
        cout << " ";

        cout << mr;

        cout << endl;
    }


    for (int i = 0; i < margin.getBottom(); i++) {
        cout << mb << endl;
    }
    cout << endl;
}

int main() {
    Padding padding = Padding();
    Margin margin = Margin();
    Border border = Border();
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
    padding.base = 3;
    margin.base = 3;
    border.base = true;
    printBlock(suka, 60, padding, margin, border);
    return 0;
}