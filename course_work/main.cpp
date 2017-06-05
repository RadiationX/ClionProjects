#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include "parser/Parser.h"
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
    unsigned long insertIndex = align == ALIGN_RIGHT ? 0 : rowString.length();
    rowString.insert(insertIndex, length, ' ');
}

void alignCenter(string &rowString, int availColumns, bool isIndented, int indent) {
    unsigned long delta = availColumns - rowString.length();
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

struct Block {
    Block *parent = NULL;
    vector<Block *> blocks;

    void addBlock(Block &block) {
        blocks.push_back(&block);
        block.parent = this;
    }

    vector<string> rows;
    string beforeText;
    string afterText;

    void setBeforeText(string &text) {
        beforeText = text;
    }

    void setAfterText(string &text) {
        afterText = text;
    }

    //vector<string> textRows;


    int availColumns = 0;
    int contentColumns = 0;
    int insetColumns = 0;
    int boxColumns = 0;

    Padding padding;
    Margin margin;
    Border border;
};

Block measureColumns(Block &block) {
    if (block.parent != NULL) {
        block.availColumns = (*block.parent).contentColumns;
    }

    block.boxColumns = block.availColumns - (block.margin.getLeft() + block.margin.getRight());
    block.insetColumns = block.boxColumns - (block.border.getLeft() + block.border.getRight());
    block.contentColumns = block.insetColumns - (block.padding.getLeft() + block.padding.getRight());
    return block;
}

Block generateBlock(Padding padding, Margin margin, Border border) {
    Block block = Block();
    block.padding = padding;
    block.margin = margin;
    block.border = border;
    return block;
}

Block generateBlock(int availColumns, Padding padding, Margin margin, Border border) {
    Block block = Block();
    block.padding = padding;
    block.margin = margin;
    block.border = border;
    block.availColumns = availColumns;

    return block;
}

Block printBlockRecurse(Block &block) {
    measureColumns(block);
    for (Block *child:block.blocks) {
        printBlockRecurse(*child);
    }

    //margins string
    string ml((unsigned long) block.margin.getLeft(), ' ');
    string mr((unsigned long) block.margin.getRight(), ' ');
    string mt((unsigned long) block.availColumns, ' ');
    string mb((unsigned long) block.availColumns, ' ');


    //paddings string
    string pl((unsigned long) block.padding.getLeft(), ' ');
    string pr((unsigned long) block.padding.getRight(), ' ');
    string pt((unsigned long) block.insetColumns, ' ');
    string pb((unsigned long) block.insetColumns, ' ');

    //borders string
    string bl((unsigned long) block.border.getLeft(), '|');
    string br((unsigned long) block.border.getRight(), '|');
    string bt((unsigned long) block.insetColumns, '-');
    string bb((unsigned long) block.insetColumns, '-');


    for (int i = 0; i < block.margin.getTop(); i++) {
        block.rows.push_back(mt);
    }
    if (block.border.getTop()) {
        string row;
        row.append(ml).append(" ").append(bt).append(" ").append(mr);
        block.rows.push_back(row);
    }
    for (int i = 0; i < block.padding.getTop(); i++) {
        string row;
        row.append(ml).append(bl).append(pt).append(br).append(mr);
        block.rows.push_back(row);
    }

    vector<string> beforeTextRows = printString(block.beforeText, block.contentColumns, ALIGN_JUSTIFY, 4);
    for (string row:beforeTextRows) {
        string newRow;
        newRow.append(ml).append(bl).append(pl).append(row).append(pr).append(br).append(mr);
        block.rows.push_back(newRow);
    }
    for (Block *child:block.blocks) {
        for (string childRow:(*child).rows) {
            string newRow;
            newRow.append(ml).append(bl).append(pl).append(childRow).append(pr).append(br).append(mr);
            block.rows.push_back(newRow);
        }
        (*child).rows.clear();
    }
    vector<string> afterTextRows = printString(block.afterText, block.contentColumns, ALIGN_JUSTIFY, 4);
    for (string row:afterTextRows) {
        string newRow;
        newRow.append(ml).append(bl).append(pl).append(row).append(pr).append(br).append(mr);
        block.rows.push_back(newRow);
    }


    for (int i = 0; i < block.padding.getBottom(); i++) {
        string row;
        row.append(ml).append(bl).append(pb).append(br).append(mr);
        block.rows.push_back(row);
    }
    if (block.border.getBottom()) {
        string row;
        row.append(ml).append(" ").append(bb).append(" ").append(mr);
        block.rows.push_back(row);
    }
    for (int i = 0; i < block.margin.getBottom(); i++) {
        block.rows.push_back(mb);
    }
    return block;
}


void printRows(vector<string> rows) {
    for (string row:rows) {
        cout << row;
        cout << endl;
    }
}

int main() {

    string htmlSource = readFile("test4.txt");
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
    cout << root->html() << endl;

    Padding padding = Padding();
    Margin margin = Margin();
    Border border = Border();
    /*string suka = "";
    suka = readFile("test3.txt");
    padding.base = 1;
    margin.base = 1;
    border.base = true;
    for (int i = 0; i < (60 *//*+ padding.base * 2 + margin.base * 2 + border.base * 2*//*); i++) {
        cout << '_';
    }
    cout << endl;
    Block block = generateBlock(60, padding, margin, border);

    Block textBlock = generateBlock(padding, margin, border);
    textBlock.setBeforeText(suka);
    textBlock.setAfterText(suka);

    Block textBlock1 = generateBlock(padding, margin, border);
    textBlock1.setBeforeText(suka);

    textBlock.addBlock(textBlock1);
    block.addBlock(textBlock);

    Block finalBLock = printBlockRecurse(block);
    printRows(finalBLock.rows);
    block.rows.clear();
    block.availColumns = 80;
    Block finalBLock2 = printBlockRecurse(block);
    printRows(finalBLock2.rows);*/
    return 0;
}