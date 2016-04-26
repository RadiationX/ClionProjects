#include <iostream>
#include <string>

using namespace std;
struct data{
    string fio;
    int points[5];
    string phone;
};

void one();

int main() {
    locale::global(locale(""));
    locale loc("");
    cout.imbue(loc);
    one();
    return 0;
}

void one() {
    FILE *file = fopen("/home/radiationx/ClionProjects.git/prog_lab3/text.txt", "rt");
    string text;
    while (!feof(file)) {
        text+=(char) fgetc(file);
    }
    int n = 1;
    for(int i = 0; i<text.size(); i++)
        if(text[i]=='\n')
            n++;

    data *datas = new data[n];

    cout<<n<<endl;

    string::size_type sz;
    n=0;
    int colon = 0;
    string temp = "";
    for (int i = 0; i < text.size()-1; i++) {
        if(text[i]==':'){
            colon++;
            temp="";
            continue;
        }
        if(text[i]=='\n'){
            n++;
            colon = 0;
            continue;
        }
        if(text[i+3]=='\0'){
            break;
        }
        if(colon==0){
            datas[n].fio+=text[i];
        } else if(colon>0&&colon<6){
            temp+=text[i];
            datas[n].points[colon-1] = stoi(temp, &sz);
        } else{
            datas[n].phone+=text[i];
        }
    }


    for(int i = 0; i<n+1;i++){
        cout<<datas[i].fio<<" : "<<datas[i].points[0]<<" : "<<datas[i].points[1]<<" : "<<datas[i].points[2]<<" : "<<datas[i].points[3]<<" : "<<datas[i].points[4]<<" : "<<datas[i].phone<<endl;
    }
    fclose(file);
}