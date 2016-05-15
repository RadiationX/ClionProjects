#include <iostream>
#include <fstream>

using namespace std;

void one();

void two();

void three();

int main() {
    /*int position = 0;
    printf("Номер задания: ");
    scanf("%d", &position);
    if (position == 1) one();
    else two();
    system("pause");*/
    three();
    return 0;
}

bool isVowel(char c) {
    return c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'i' || c == 'I' || c == 'o' || c == 'O' || c == 'u' ||
           c == 'U';
}

void one() {
    FILE *file = fopen("/home/radiationx/ClionProjects.git/prog_lab_2/text_1.txt", "rt");
    int counter = 0, words = 0, punctuations = 0;
    char buff, text[256];
    while (!feof(file)) {
        for (; counter < 255; counter++) {
            buff = (char) fgetc(file);
            text[counter] = buff;
            if (buff == '\n') {
                text[counter] = '\0';
                break;
            }
        }
        text[counter] = '\0';
    }
    for (int i = 0; i < 256; i++) {
        if ((text[i] == ' ') && (text[i + 1] != ' ') && (text[i + 1] != '\0'))
            words++;

        if (text[i] == ',' || text[i] == '.' || text[i] == ':' || text[i] == ';')
            punctuations++;
    }
    if (words / punctuations <= 6) {
        printf("Текст в достаточной мере обогащен знаками препинания");
    } else {
        printf("Текст в недостаточной мере обогащен знаками препинания");
    }
    fclose(file);
}

void two() {
    FILE *file = fopen("/home/radiationx/ClionProjects.git/prog_lab_2/text_1.txt", "rt");
    FILE *output_text = fopen("/home/radiationx/ClionProjects.git/prog_lab_2/out.txt", "wt");
    int length = 0;
    char buff, text[256];
    while (!feof(file)) {
        buff = (char) fgetc(file);
        if (length <= 255) {
            text[length] = buff;
            length++;
        }
    }
    text[length] = ' ';
    int prevWordIndex = 0, vowels = 0, vowelsTemp = 0, counter = 0;
    for (int i = 0; i < length; i++) {
        if (((text[i] == ' ') && (text[i + 1] != ' ') || (text[i] == '\n') && (text[i + 1] != ' \n')) &&
            (text[i + 1] != '\0')) {
            for (int j = prevWordIndex; j < i; j++) {
                if (vowels < 4 && (isVowel(text[j]))) {
                    vowels++;
                    vowelsTemp++;
                }
                if (vowels >= 4) {
                    if (vowelsTemp == 4) {
                        j = prevWordIndex;
                        vowelsTemp = 0;
                    }

                    if (isVowel(text[j])) {
                        text[j] = counter + 1 + '0';
                        counter++;
                    }
                }

            }
            vowels = vowelsTemp = counter = 0;
            prevWordIndex = i;
        }
    }
    fprintf(output_text, "%s\n", text);
    fclose(file);
    fclose(output_text);
}

void three() {
    ifstream fin("text_3.txt", ios::in);
    ofstream fout("out_3.txt", ios::out);
    string text = "";
    string temp;
    string result;
    int i = 0;
    while(!fin.eof()){
        fin>>temp;
        if (i!=0) text+=" ";
        text+=temp;
        i++;
    }

    for (int i = 0; i < text.size(); i++){
        if ((text[i] != ' ' && text[i + 1] != ' ' && (text[i - 1] == '\0' || text[i - 1] == ' ')) | text[i] == ' '){
            result += text[i];
        }
    }
    fout<<result;
    fin.close();
    fout.close();
}