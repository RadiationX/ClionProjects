//
// Created by radiationx on 05.06.17.
//

#ifndef COURSE_WORK_BLOCK_H
#define COURSE_WORK_BLOCK_H

#include "iostream"
#include "vector"
#include "string"
#include "Params.h"

using namespace std;

class Block {
public:
    Block *parent = NULL;
    vector<Block *> blocks;

    vector<string> rows;
    string text;
    string afterText;

    Params params;

    int availColumns = 0;
    int contentColumns = 0;
    int insetColumns = 0;
    int boxColumns = 0;

    void addBlock(Block &block) {
        blocks.push_back(&block);
        block.parent = this;
    }

    void setText(string text) {
        this->text = text;
    }

    void setAfterText(string text) {
        afterText = text;
    }
};


#endif //COURSE_WORK_BLOCK_H
