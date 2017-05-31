#include <iostream>
#include <string>
#include <regex>
#include <thread>
#include <unistd.h>
#include "parser/Document.h"

using namespace std;

int main() {

    cout << "Hello, World!" << endl;
    string s("<div>asdf<span>hey bro wassup?</span>\n<strong>suck my dick nigga!</strong>hgfhj</div>");
    /*smatch m;
    regex e("(?:<(?:!--[\\s\\S]*?--|(?:(script|style)(?: )?([^>]*)>)([\\s\\S]*?)(?:<\\/\\1)|([\\/])?([\\w]*)(?: ([^>]*))?\\/?)>)(?:([^<]+))?");   // matches words beginning by "sub"

    cout << "Target sequence: " << s << endl;
    cout << "Regular expression: /\\b(sub)([^ ]*)/" << endl << endl;
    cout << "The following matches and submatches were found:" << endl;


    string temp = s;
    while (regex_search(temp, m, e)) {
        cout << "Matched:" << endl;
        for (int i = 0; i < m.size(); i++) {
            string suka = m[i];
            cout << "\t" << i << ": " << suka << " : " << suka.length() << endl;
        }
        cout << endl;
        temp = m.suffix().str();
    }*/
    ElementsList<Element> elements;
    for (int i = 0; i < 4; i++) {
        Element *element = new Element("suka");
        cout << "ADD ELEM: " << element << endl;
        elements.push_back(element);
    }
    cout << endl;

    for (int i = 0; i < 4; i++) {
        cout << "VECTOR: " << elements.get(i) << " : " << elements.get(i)->getTagName() << endl;
    }
    //return 0;
    Document *document = new Document();
    document->parse(s);

    cout << document->html();
    return 0;
}