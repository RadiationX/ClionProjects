#include <iostream>
#include <string>
#include <regex>
#include <thread>
#include <unistd.h>
#include "parser/Document.h"
#include <fstream>

using namespace std;
using namespace std::chrono;

static string basePath = "/Users/radiationx/ClionProjects/ClionProjects/course_work/";

string readHtml(string fileName) {
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

int main() {
    string htmlSource = readHtml("test2.txt");
    Document *document = new Document();
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    //usleep(750 * 1000);

    //cout<<htmlSource;
    //string s(            "<div sukalol=\"true\">кирилица<span>hey bro wassup?</span>\n<strong>suck my dick nigga!</strong>hgfhj</div>");


    document->parse(htmlSource);
    cout << endl;


    high_resolution_clock::time_point t2 = high_resolution_clock::now();


    auto duration = duration_cast<microseconds>(t2 - t1).count() / 1000;
    cout << duration;
    //cout << document->html() << endl;
    return 0;
}