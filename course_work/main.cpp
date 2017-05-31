#include <iostream>
#include <string>
#include <regex>
#include <thread>
#include <unistd.h>
#include "parser/Document.h"

using namespace std;

int main() {
    string s("<div sukalol=\"true\">кирилица<span>hey bro wassup?</span>\n<strong>suck my dick nigga!</strong>hgfhj</div>");

    Document *document = new Document();
    document->parse(s);
    cout<<endl;

    cout << document->html() << endl;
    return 0;
}