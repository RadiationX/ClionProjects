//
// Created by radiationx on 31.05.17.
//

#ifndef COURSE_WORK_ELEMENT_H
#define COURSE_WORK_ELEMENT_H

#include <vector>
#include "iostream"
#include "string"
#include "ElementsList.h"

using namespace std;

class Element {

private :
    //vector<Element> elements/* = new vector<Element>()*/;
    ElementsList<Element> elements/* = new vector<Element>()*/;
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

    string getTagName() {
        return tagName;
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
        this->afterText = this->afterText.append(afterText);
    }

    void addText(string text) {
        if (text.length() == 0) return;
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
        cout << "DOCUMENT ADD TO ELEMENTS " << elements.back() << endl;
    }

    Element *getLast() {
        return elements.back();
    }

    string html() {
        return html(this, true);
    }

    string htmlNoParent() {
        return "";
    }

    string getAllText() {
        return "";
    }

    ElementsList<Element> getElements() {
        return elements;
    }

    string getAfterText() {
        return afterText;
    }

    string html(Element *element, bool withParent) {
        cout << "SUKA " << &element << " : " << element->getTagName() << endl;
        string html = "";
        if (withParent) {
            html.append("<").append(element->getTagName());
            /*if (!element->getAttrsSource().isEmpty()) {
                html.append(" ").append(element->getAttrsSource());
            }*/
            html.append(">");
        }

        if (element->getText().length() > 0) {
            html.append(element->getText());
        }

        for (int i = 0; i < element->getElements().size(); i++) {
            string suka = this->html(element->getElements().get(i), true);
            html.append(suka);
        }


        if (withParent) {
            //if (!containsInUTag(element->tagName()))
            html.append("</").append(element->getTagName()).append(">");

            if (element->getAfterText().length() > 0)
                html.append(element->getAfterText());
        }
        return html;
    }
};

#endif //COURSE_WORK_ELEMENT_H
