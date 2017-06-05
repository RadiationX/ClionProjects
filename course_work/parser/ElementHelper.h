//
// Created by radiationx on 31.05.17.
//

#ifndef COURSE_WORK_ELEMENTHELPER_H
#define COURSE_WORK_ELEMENTHELPER_H

#include <regex>
#include "iostream"
#include "string"

using namespace std;

class ElementHelper {
private:
    regex *spaceRemover = new regex(" {2,}");
    regex *attrPattern;
    string uTags[17] = {"area", "area", "br", "col", "colgroup", "command", "embed", "hr", "img", "input", "keygen",
                        "link", "meta", "param", "source", "track", "wbr"};

    ElementHelper() {}

    ~ElementHelper() {}


    ElementHelper(ElementHelper const &) = delete;

    ElementHelper &operator=(ElementHelper const &) = delete;

public:


    static ElementHelper &Instance() {
        static ElementHelper s;
        return s;
    }

    regex *getAttrPattern() {
        if (attrPattern == NULL) {
            attrPattern = new regex("([^ \"]*?)\\s*?=\\s*?[\"']([^\"']*)[\"']");
        }
        return attrPattern;
    }

    string *getUTags() {
        return uTags;
    }

    bool containsInUTag(string tag) {
        for (string uTag : ElementHelper::Instance().uTags)
            if (uTag.compare(tag) == 0) return true;
        return false;
    }


    string removeSpaces(string s) {
        return regex_replace(s, *spaceRemover, " ");
    }
};

#endif //COURSE_WORK_ELEMENTHELPER_H
