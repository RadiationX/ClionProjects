//
// Created by radiationx on 05.06.17.
//

#ifndef COURSE_WORK_PARAMS_H
#define COURSE_WORK_PARAMS_H

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
    bool base = true;
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


class Params {
public:
    static const int ALIGN_LEFT = 0;
    static const int ALIGN_RIGHT = 1;
    static const int ALIGN_CENTER = 2;
    static const int ALIGN_JUSTIFY = 3;
    int align = 0;
    int indent = 0;
    Padding padding = Padding();
    Margin margin = Margin();
    Border border = Border();
};


#endif //COURSE_WORK_PARAMS_H
