#include <iostream>
#include <fstream>

using namespace std;

int main() {
    string line;
    ifstream myfile("/home/radiationx/ClionProjects.git/prog_lab_2/text_1.txt");
    if (myfile.is_open()) {
        while (myfile.good()) {
            getline(myfile, line);
            cout << line << endl;
        }
        myfile.close();
    }

    else cout << "Unable to open file";







    /*FILE *input_text = fopen("input.txt", "rt");
    FILE *output_text = fopen("output.txt", "wt");
    int counter;
    char t = 0;
    char buffer[80];
    while (!feof(input_text)) {
        for (counter = 0; counter < 79; counter++) {
            t = fgetc(input_text);
            buffer[counter] = t;
            if (t == '\n' || feof(input_text)) {
                buffer[counter] = '\0';
                break;
            }
        }
        buffer[counter] = '\0';
        for (int i = 0; i < 80 - counter; i++)
            fputc(' ', output_text);
        fprintf(output_text, "%s\n", buffer);
    }
    fclose(input_text);
    fclose(output_text);*/
    return 0;
}