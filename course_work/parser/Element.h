//
// Created by radiationx on 31.05.17.
//

#ifndef COURSE_WORK_ELEMENT_H
#define COURSE_WORK_ELEMENT_H

#include <vector>
#include <iostream>
#include <string>
#include "ElementHelper.h"

using namespace std;

class Element {

private :
    vector<Element *> elements;
    vector<pair<string, string>> *attributes = NULL;
    Element *parent;
    string text = "";
    string afterText = "";
    string tagName = "ERROR-TAG";
    int level = 0;
    string attrSource = "";

public:

    Element(string tagName) {
        this->tagName = tagName;
    }

    Element(string tagName, string attrs) {
        this->tagName = tagName;
        this->attrSource = attrs;
    }


    string attr(string key) {
        for (pair<string, string> p : *getAttributes()) {
            if (p.first.compare(key) == 0) {
                return p.second;
            }
        }
        return "";
    }


    vector<pair<string, string>> *getAttributes() {
        if (attributes == NULL) {
            attributes = parseAttributes(attrSource, new vector<pair<string, string>>());
        }
        return attributes;
    }

    string getTagName() {
        return tagName;
    }

    string getAttrSource() {
        return attrSource;
    }

    void setParent(Element *parent) {
        this->parent = parent;
    }

    Element *getParent() {
        return parent;
    }

    string getText() {
        return text;
    }

    void setText(string text) {
        this->text = text;
    }

    void setAfterText(string afterText) {
        this->afterText = afterText;
    }

    void addAfterText(string afterText) {
        if (afterText.length() == 0) return;
        afterText = ElementHelper::Instance().removeSpaces(afterText);
        if (afterText.length() == 1 && isspace(afterText[0]))
            return;
        this->afterText = this->afterText.append(afterText);
    }

    void addText(string text) {
        if (text.length() == 0) return;
        text = ElementHelper::Instance().removeSpaces(text);
        if (text.length() == 1 && isspace(text[0]))
            return;
        this->text = this->text.append(text);
    }

    void setLevel(int level) {
        this->level = level;
    }

    int getLevel() {
        return level;
    }

    void add(Element *element) {
        elements.push_back(element);
    }

    Element *getLast() {
        return elements.back();
    }

    string html() {
        return getHtml(this, true);
    }

    string htmlNoParent() {
        return getHtml(this, false);
    }

    string getAllText() {
        return getAllText(this);
    }

    vector<Element *> getElements() {
        return elements;
    }

    string getAfterText() {
        return afterText;
    }

    static string getHtml(Element *element, bool withParent) {
        string resultHtml = "";
        if (withParent) {
            resultHtml.append("<").append(element->getTagName());
            if (element->getAttrSource().length() > 0) {
                resultHtml.append(" ").append(element->getAttrSource());
            }
            resultHtml.append(">");
        }

        if (element->getText().length() > 0) {
            resultHtml.append(element->getText());
        }

        for (int i = 0; i < element->getElements().size(); i++) {
            string suka = getHtml(element->getElements().at(i), true);
            resultHtml.append(suka);
        }


        if (withParent) {
            if (!ElementHelper::Instance().containsInUTag(element->getTagName()))
                resultHtml.append("</").append(element->getTagName()).append(">");

            if (element->getAfterText().length() > 0)
                resultHtml.append(element->getAfterText());
        }
        return resultHtml;
    }

    static string getAllText(Element *element) {
        string text = "";
        text.append(" ").append(element->getText());

        for (int i = 0; i < element->getElements().size(); i++) {
            text.append(getAllText(element->getElements().at(i)));
        }

        text.append(" ").append(element->getAfterText());
        return text;
    }

    static vector<pair<string, string>> *parseAttributes(string source, vector<pair<string, string>> *attrs) {
        if (source.length() > 0) {
            smatch m;
            string temp = source;

            while (regex_search(temp, m, *ElementHelper::Instance().getAttrPattern())) {
                pair<string, string> *newPair = new pair<string, string>(m[1], m[2]);
                attrs->push_back(*newPair);
                temp = m.suffix().str();
            }
        }
        return attrs;
    }
};

#endif //COURSE_WORK_ELEMENT_H
