//
// Created by radiationx on 31.05.17.
//

#ifndef COURSE_WORK_DOCUMENT_H
#define COURSE_WORK_DOCUMENT_H

#include <list>
#include <regex>
#include "iostream"
#include "string"
#include "Element.h"
#include "ElementHelper.h"

using namespace std;

class Document {
private:
    regex *mainPattern;
    Element *root;


public:
    Document() {
        mainPattern = new regex(
                "(?:<(?:!--[\\s\\S]*?--|(?:(script|style)(?: )?([^>]*)>)([\\s\\S]*?)(?:<\\/\\1)|([\\/])?([\\w]*)(?: ([^>]*))?\\/?)>)(?:([^<]+))?");
    }

    Document *parse(string html) {
        ElementsList<Element> openedTags;
        vector<string> errorTags;
        Element *lastOpened = NULL;
        Element *lastClosed = NULL;
        Element *newElement = NULL;
        //ssTag - блоки script/style, т.к в них может быть всякая дичь
        string tag, text, afterText, ssTag;
        bool ssTagNull;
        //Matcher m = mainPattern.matcher(getHtml);
        smatch m;
        int tags = 0, comments = 0, resolvedErrors = 0, openTagsCount = 0, closeTagsCount = 0;
        string temp = html;

        while (regex_search(temp, m, *mainPattern)) {
            //cout<<m[0]<<endl;
            tags++;
            //Более удобное обращение к последнему открытому тегу
            if (openedTags.size() > 0)
                lastOpened = openedTags.at(openedTags.size() - 1);

            //Выбор название тега
            ssTag = m[1];
            ssTagNull = ssTag.length() == 0;
            tag = m[5];

            //true в том случае, когда попадается комментарии
            if (tag.length() == 0 && ssTagNull) {
                comments++;
                //Если нет последнего закрытого элемента, то попавшийся текст добавляется в тело элемента
                //Иначе добавляется как текст после элемента
                if (lastClosed == NULL) {
                    if (lastOpened != NULL)
                        lastOpened->addText(m[0]);
                } else {
                    lastClosed->addAfterText(m[0]);
                }
                //Нет смысла продолжать выполнение
                temp = m.suffix().str();
                continue;
            }

            //Выбор текста
            afterText = m[7];
            text = ssTagNull ? afterText : m[3];

            //NULL в том случае, когда тег открывается
            if ((m[4].length() == 0) | !ssTagNull) {
                //ВЕТВЬ 1.1: Создание и добавление элемента

                openTagsCount++;
                //Группа 3 - аттрибуты тега, добавляются сразу для уменьшения времени парсинга
                newElement = new Element(ssTagNull ? tag : ssTag, m[ssTagNull ? 6 : 2]);

                //Уровень вложенности элемента. Совпадает с кол-вом открытых тегов
                newElement->setLevel((int) openedTags.size());

                if (lastOpened != NULL) {
                    //Устанавливается родитель элемента.
                    //Истинно, когда в одном родителе идёт несколько последовательно вложенных элементов
                    //<div>
                    //  Последовательно выложенные:
                    //  <div></div>
                    //  <div></div>
                    //  <div></div>
                    //</div>
                    newElement->setParent(
                            lastOpened->getLevel() == openedTags.size() ? lastOpened->getParent() : lastOpened);
                }

                this->add(newElement);

                //Проверка на теги, которые можно не закрывать
                if (!ssTagNull | ElementHelper::Instance().containsInUTag(newElement->getTagName())) {

                    //Добавляем текст внутри script/style
                    if (!ssTagNull) {
                        newElement->addText(text);
                    }
                    //Т.к. у незакрывающегося тега нет тела, то текст добавляется после него
                    newElement->addAfterText(afterText);

                    //Т.к. тег неявно закрывающийся, то последний закрытый тег это он
                    lastClosed = newElement;
                    closeTagsCount++;
                } else {
                    //Есть тело элемента, добавляем текст
                    newElement->addText(text);

                    //Добавляем в список открытых элементов
                    openedTags.push_back(newElement);

                    //Делаем NULL, потому-что иначе будет неверно добавляться script/sty
                    lastClosed = NULL;
                }
            } else {
                //ВЕТВЬ 1.2: Закрытие элемента и исправление ошибок в getHtml
                if (lastOpened != NULL) {


                    lastClosed = lastOpened;

                    //На случай, если допущена ошибка и есть лишний закрывающий тег
                    //<span><b></span></b>
                    //<span></b></span>
                    //<span><b></span>
                    if (lastClosed->getTagName().compare(tag) != 0) {
                        bool resolved = false;

                        //Исправление ошибки с переносом элемента внутрь
                        for (long i = errorTags.size() - 1; i >= 0; i--) {
                            string errorTag = (string &) errorTags.at(i);
                            if (errorTag.compare(tag) == 0) {
                                //Если последний в последнем или последний в последнем в последнем тег равен тегу по разметке
                                //На случай когда есть в errorTags, но уже исправлено
                                if (lastClosed->getLast() != NULL && (lastClosed->getLast()->getLast() != NULL &&
                                                                      lastClosed->getLast()->getLast()->getTagName().compare(
                                                                              tag) == 0 |
                                                                      lastClosed->getLast()->getTagName().compare(
                                                                              tag) ==
                                                                      0)) {
                                    errorTags.erase(errorTags.begin() + i);
                                    resolved = true;
                                    break;
                                }
                                //Создаем элемент и вставляем в последний, с переносом текста
                                //Так решается ошибка в хроме например
                                Element *resolveElement = new Element(errorTag);
                                resolveElement->setLevel(lastClosed->getLevel() + 1);
                                resolveElement->setParent(lastClosed);
                                resolveElement->setText(lastClosed->getText());
                                lastClosed->setText("");
                                this->add(resolveElement);
                                lastClosed = NULL;
                                resolved = true;
                                errorTags.erase(errorTags.begin() + i);
                                break;
                            }
                        }
                        //Если ошибка исправлена, то продолжать смысла нет
                        if (resolved) {
                            resolvedErrors++;
                            temp = m.suffix().str();
                            continue;
                        }

                        //Добавляем в список ошибок
                        errorTags.push_back(lastClosed->getTagName());

                        //Закрываем тег
                        openedTags.remove(openedTags.begin() + openedTags.size() - 1);
                        closeTagsCount++;

                        //Исправление ошибки с правильным выносом элемента
                        if (openedTags.size() > 0) {
                            if (openedTags.at(openedTags.size() - 1)->getTagName().compare(tag) == 0) {
                                openedTags.remove(openedTags.begin() + openedTags.size() - 1);
                                closeTagsCount++;
                                lastClosed = NULL;
                                resolvedErrors++;
                                temp = m.suffix().str();
                                continue;
                            }
                        }
                        temp = m.suffix().str();
                        continue;
                    }


                    //Добавляем текст после закрывающего тега
                    lastClosed->addAfterText(afterText);

                    //Удаляем/"закрываем" тег
                    openedTags.remove(openedTags.begin() + openedTags.size() - 1);
                    closeTagsCount++;
                }
            }
            temp = m.suffix().str();
        }

        cout << endl;
        cout << "QualityControl: "
             << "Main Info {AllTags: " << tags << "; ErrorTags: " << errorTags.size() << "; ResolvedErrors : " <<
             resolvedErrors << "; UnclosedTags: " << openedTags.size() << "}" << endl;
        cout << "QualityControl: " <<
             "More Info {Comments: " << comments << "; OpenedTags: " << openTagsCount << "; ClosedTags: " <<
             closeTagsCount << "}" << endl;
        /*for (Element el : openedTags.toArray()) {
            Log.e("QualityControl", "Unclosed Tag: " << el.getTagName());
        }
        for (string el : errorTags) {
            Log.e("QualityControl", "Error Tag: " << el);
        }*/
        return this;
    }


    void findToAdd(Element *root, Element *children) {
        if (children->getLevel() - 1 == root->getLevel()) {
            root->add(children);
        } else {
            findToAdd(root->getLast(), children);
        }
    }

    void add(Element *children) {
        if (children->getLevel() == 0) {
            root = children;
            return;
        }
        findToAdd(root, children);
    }

    Element *getRoot() {
        return root;
    }

    string html() {
        return root->html();
    }

    string htmlNoParent() {
        return root->htmlNoParent();
    }

    string getAllText() {
        return root->getAllText();
    }
};


#endif //COURSE_WORK_DOCUMENT_H
