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
    vector<Block *> blocks;

    void addBlock(Block &block) {
        blocks.push_back(&block);
    }

    vector<string> rows;
    vector<string> textRows;


    int availColumns = 0;
    int contentColumns = 0;
    int insetColumns = 0;
    int boxColumns = 0;

    Padding padding;
    Margin margin;
    Border border;
};

Block generateBlock(int availColumns, Padding padding, Margin margin, Border border) {
    Block block = Block();
    block.availColumns = availColumns;
    block.contentColumns =
            availColumns - (margin.getLeft() + padding.getRight() + padding.getLeft() + margin.getRight() +
                            border.getLeft() + border.getRight());
    block.insetColumns = block.contentColumns + (padding.getLeft() + padding.getRight());
    block.boxColumns = block.insetColumns + (border.getLeft() + border.getRight());
    block.padding = padding;
    block.margin = margin;
    block.border = border;
    return block;
}

Block printBlock(Block &block, Padding padding, Margin margin, Border border) {

    /*Block result = Block();
    result.contentColumns = block.contentColumns;
    result.insetColumns = block.insetColumns;
    result.boxColumns = block.boxColumns;*/

    Block result = generateBlock(block.contentColumns, padding, margin, border);



    //margins string
    string ml(margin.getLeft(), ' ');
    string mr(margin.getRight(), ' ');
    string mt(block.availColumns, ' ');
    string mb(block.availColumns, ' ');


    //paddings string
    string pl(padding.getLeft(), ' ');
    string pr(padding.getRight(), ' ');
    string pt(block.insetColumns, ' ');
    string pb(block.insetColumns, ' ');

    //borders string
    string bl(border.getLeft(), '|');
    string br(border.getRight(), '|');
    string bt(block.insetColumns, '-');
    string bb(block.insetColumns, '-');


    for (int i = 0; i < margin.getTop(); i++) {
        result.rows.push_back(mt);
    }
    if (border.getTop()) {
        string row;
        row.append(ml).append(" ").append(bt).append(" ").append(mr);
        result.rows.push_back(row);
    }
    for (int i = 0; i < padding.getTop(); i++) {
        string row;
        row.append(ml).append(bl).append(pt).append(br).append(mr);
        result.rows.push_back(row);
    }


    for (string row:block.rows) {
        string newRow;
        newRow.append(ml).append(bl).append(pl).append(row).append(pr).append(br).append(mr);
        result.rows.push_back(newRow);
    }


    for (int i = 0; i < padding.getBottom(); i++) {
        string row;
        row.append(ml).append(bl).append(pb).append(br).append(mr);
        result.rows.push_back(row);
    }
    if (border.getBottom()) {
        string row;
        row.append(ml).append(" ").append(bb).append(" ").append(mr);
        result.rows.push_back(row);
    }
    for (int i = 0; i < margin.getBottom(); i++) {
        result.rows.push_back(mb);
    }
    return result;
}

Block printBlockRecurse(Block &block) {
    cout << &block << " printBlockRecurse " << block.blocks.size() << " : " << block.rows.size() << endl;
    cout << &block << " params " << block.padding.base << " : " << block.margin.base << " : " << block.border.base
         << " | "
         << block.availColumns << " : " << block.boxColumns << " : " << block.insetColumns << " : "
         << block.contentColumns << endl;
    for (Block *child:block.blocks) {
        Block returned = printBlockRecurse(*child);
        cout << "RETURNED CHILD " << &returned << endl;
    }

    //margins string
    string ml(block.margin.getLeft(), ' ');
    string mr(block.margin.getRight(), ' ');
    string mt(block.availColumns, ' ');
    string mb(block.availColumns, ' ');


    //paddings string
    string pl(block.padding.getLeft(), ' ');
    string pr(block.padding.getRight(), ' ');
    string pt(block.insetColumns, ' ');
    string pb(block.insetColumns, ' ');

    //borders string
    string bl(block.border.getLeft(), '|');
    string br(block.border.getRight(), '|');
    string bt(block.insetColumns, '-');
    string bb(block.insetColumns, '-');


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

    for (string row:block.textRows) {
        string newRow;
        newRow.append(ml).append(bl).append(pl).append(row).append(pr).append(br).append(mr);
        block.rows.push_back(newRow);
        cout << &block << " print this row" << newRow << endl;
    }
    for (Block *child:block.blocks) {
        cout << &block << " try print child " << &child << " : " << (*child).rows.size() << endl;
        for (string childRow:(*child).rows) {
            cout << "print child row" << childRow << endl;
            string newRow;
            newRow.append(ml).append(bl).append(pl).append(childRow).append(pr).append(br).append(mr);
            block.rows.push_back(newRow);
        }
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
    cout << "after printBlockRecurse " << block.blocks.size() << " : " << block.rows.size() << endl;
    return block;
}

Block printBlock(string &text, int availColumns, Padding padding, Margin margin, Border border) {
    Block block = generateBlock(availColumns, padding, margin, border);
    vector<string> rows = printString(text, block.contentColumns, ALIGN_JUSTIFY, 4);
    block.rows = rows;
    return printBlock(block, padding, margin, border);
}

Block generateTextBlock(string &text, int availColumns, Padding padding, Margin margin, Border border) {
    Block block = generateBlock(availColumns, padding, margin, border);
    block.textRows = printString(text, block.contentColumns, ALIGN_JUSTIFY, 4);
    return block;
}

void printRows(vector<string> rows) {
    for (string row:rows) {
        cout << row;
        cout << endl;
    }
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
    padding.base = 1;
    margin.base = 1;
    border.base = true;
    for (int i = 0; i < (60 /*+ padding.base * 2 + margin.base * 2 + border.base * 2*/); i++) {
        cout << '_';
    }
    cout << endl;
    Block block = generateBlock(60, padding, margin, border);
    Block textBlock = generateTextBlock(suka, block.contentColumns, padding, margin, border);
    Block textBlock2 = generateTextBlock(suka, textBlock.contentColumns, padding, margin, border);
    block.addBlock(textBlock);
    textBlock.addBlock(textBlock2);
    Block finalBLock = printBlockRecurse(block);
    printRows(finalBLock.rows);
    return 0;
}