//
// Created by radiationx on 05.06.17.
//

#ifndef COURSE_WORK_CONSOLEVIEW_H
#define COURSE_WORK_CONSOLEVIEW_H

#include "iostream"
#include "../parser/Element.h"
#include "Block.h"

using namespace std;

class ConsoleView {
public:
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

    void alignBase(int align, string &rowString, int availColumns, bool isIndented, int indent) {
        unsigned long length = availColumns - rowString.length();
        unsigned long insertIndex = align == Params::ALIGN_RIGHT ? 0 : rowString.length();
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
            int offsetHead = 0;
            int offsetTail = 0;
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
                offsetHead++;
            }

            //"Убираем" пробелы вконце
            while (isspace(s[tailIndex - 1])) {
                tailIndex--;
                offsetTail++;
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
                case Params::ALIGN_JUSTIFY:
                    alignJustify(rowString, availColumns, isIndented, indent);
                    break;
                case Params::ALIGN_CENTER:
                    alignCenter(rowString, availColumns, isIndented, indent);
                    break;
                case Params::ALIGN_LEFT:;
                case Params::ALIGN_RIGHT:;
                default:
                    alignBase(align, rowString, availColumns, isIndented, indent);
                    break;
            }

            result.push_back(rowString);

            //Смещаем индексы вперед по строке
            lengthToPrint += startIndex;
            startIndex = lengthToPrint;

            rowsCount++;
            if (startIndex + offsetHead + offsetTail > len) {
                break;
            }
        }
        return result;
    }

    Block measureColumns(Block &block) {
        if (block.parent != NULL) {
            block.availColumns = (*block.parent).contentColumns;
        }

        block.boxColumns = block.availColumns - (block.params.margin.getLeft() + block.params.margin.getRight());
        block.insetColumns = block.boxColumns - (block.params.border.getLeft() + block.params.border.getRight());
        block.contentColumns = block.insetColumns - (block.params.padding.getLeft() + block.params.padding.getRight());
        return block;
    }

    Block generateBlock(Padding padding, Margin margin, Border border) {
        Block block = Block();
        block.params.padding = padding;
        block.params.margin = margin;
        block.params.border = border;
        return block;
    }

    Block generateBlock(int availColumns, Padding padding, Margin margin, Border border) {
        Block block = generateBlock(padding, margin, border);
        block.availColumns = availColumns;
        return block;
    }

    Block printBlockRecurse(Block &block) {
        measureColumns(block);
        for (Block *child:block.blocks) {
            printBlockRecurse(*child);
        }

        //margins string
        string ml((unsigned long) block.params.margin.getLeft(), ' ');
        string mr((unsigned long) block.params.margin.getRight(), ' ');
        string mt((unsigned long) block.availColumns, ' ');
        string mb((unsigned long) block.availColumns, ' ');


        //paddings string
        string pl((unsigned long) block.params.padding.getLeft(), ' ');
        string pr((unsigned long) block.params.padding.getRight(), ' ');
        string pt((unsigned long) block.insetColumns, ' ');
        string pb((unsigned long) block.insetColumns, ' ');

        //borders string
        string bl((unsigned long) block.params.border.getLeft(), '|');
        string br((unsigned long) block.params.border.getRight(), '|');
        string bt((unsigned long) block.insetColumns, '-');
        string bb((unsigned long) block.insetColumns, '-');


        for (int i = 0; i < block.params.margin.getTop(); i++) {
            block.rows.push_back(mt);
        }
        if (block.params.border.getTop()) {
            string row;
            row.append(ml).append(" ").append(bt).append(" ").append(mr);
            block.rows.push_back(row);
        }
        for (int i = 0; i < block.params.padding.getTop(); i++) {
            string row;
            row.append(ml).append(bl).append(pt).append(br).append(mr);
            block.rows.push_back(row);
        }

        vector<string> beforeTextRows = printString(block.text, block.contentColumns, block.params.align,
                                                    block.params.indent);
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


        for (int i = 0; i < block.params.padding.getBottom(); i++) {
            string row;
            row.append(ml).append(bl).append(pb).append(br).append(mr);
            block.rows.push_back(row);
        }
        if (block.params.border.getBottom()) {
            string row;
            row.append(ml).append(" ").append(bb).append(" ").append(mr);
            block.rows.push_back(row);
        }
        for (int i = 0; i < block.params.margin.getBottom(); i++) {
            block.rows.push_back(mb);
        }
        Block basic = block.parent == NULL ? block : *block.parent;
        vector<string> afterTextRows = printString(block.afterText, basic.contentColumns, basic.params.align,
                                                   basic.params.indent);
        for (string row:afterTextRows) {
            string newRow;
            //newRow.append(ml).append(bl).append(pl).append(row).append(pr).append(br).append(mr);
            newRow.append(row);
            block.rows.push_back(newRow);
        }
        return block;
    }

    Block *transformToBlock(Element *root, Block *parentBlock) {
        cout << "TRANSFORM " << root->getTagName() << endl;
        Block *block = new Block();
        block->parent = parentBlock;

        vector<pair<string, string>> attributes = *root->getAttributes();
        for (pair<string, string> attribute:attributes) {
            string key = attribute.first;
            string value = attribute.second;
            if (key.compare("align") == 0) {
                if (value.compare("left") == 0) {
                    block->params.align = Params::ALIGN_LEFT;
                } else if (value.compare("right") == 0) {
                    block->params.align = Params::ALIGN_RIGHT;
                } else if (value.compare("center") == 0) {
                    block->params.align = Params::ALIGN_CENTER;
                } else if (value.compare("justify") == 0) {
                    block->params.align = Params::ALIGN_JUSTIFY;
                } else {
                    block->params.align = Params::ALIGN_LEFT;
                }
            } else if (strContains(key, "padding")) {
                int paddingValue = atoi(value.c_str());

                if (strContains(key, "left")) {
                    block->params.padding.left = paddingValue;
                } else if (strContains(key, "top")) {
                    block->params.padding.top = paddingValue;
                } else if (strContains(key, "right")) {
                    block->params.padding.right = paddingValue;
                } else if (strContains(key, "bottom")) {
                    block->params.padding.bottom = paddingValue;
                } else {
                    block->params.padding.base = paddingValue;
                }
            } else if (strContains(key, "margin")) {
                int marginValue = atoi(value.c_str());

                if (strContains(key, "left")) {
                    block->params.margin.left = marginValue;
                } else if (strContains(key, "top")) {
                    block->params.margin.top = marginValue;
                } else if (strContains(key, "right")) {
                    block->params.margin.right = marginValue;
                } else if (strContains(key, "bottom")) {
                    block->params.margin.bottom = marginValue;
                } else {
                    block->params.margin.base = marginValue;
                }
            } else if (strContains(key, "border")) {
                bool borderValue = atoi(value.c_str()) > 0;

                if (strContains(key, "left")) {
                    block->params.border.left = borderValue;
                } else if (strContains(key, "top")) {
                    block->params.border.top = borderValue;
                } else if (strContains(key, "right")) {
                    block->params.border.right = borderValue;
                } else if (strContains(key, "bottom")) {
                    block->params.border.bottom = borderValue;
                } else {
                    block->params.border.base = borderValue;
                }
            }
        }
        if (block->parent != NULL) {
            if (block->params.align < block->parent->params.align) {
                block->params.align = block->parent->params.align;
            }
        }
        cout << "ALIGN " << block->params.align << " : " << (block->parent == NULL ? -1 : block->parent->params.align)
             << endl;
        block->setText(root->getText());
        block->setAfterText(root->getAfterText());

        for (Element *element:root->getElements()) {
            Block *newBlock = transformToBlock(element, block);
            block->addBlock(*newBlock);
        }
        return block;
    }

    bool strContains(string s1, string s2) {
        return s1.find(s2) != string::npos;
    }

};


#endif //COURSE_WORK_CONSOLEVIEW_H
