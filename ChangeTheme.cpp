#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string path = "SomeRouteFile";

string themes[2] = {"mocha", "latte"};
string text = "";

// return 1: themeMocha, return 2: themeLatte, return 0: control

bool VerifyText (string TextSrc, string Findtext, int initial, int init) {
    bool flag = 1;
    
    if (initial + Findtext.size() > TextSrc.size()) return 0;

    for (int i = init; i < Findtext.size(); i++) {

        if (TextSrc[initial + i] != Findtext[i]) flag = 0;
    }
    return flag;

}

int checkTheme(string textImport) {
    int control = -1;
    int i = 0, j;
    while(i < textImport.size()) {
        if (textImport[i] == 'm') {
            control = (VerifyText(textImport, themes[0], i, 1) == 1) ? 1: 0;
            i += themes[0].size() - 1;
        }
        else if (textImport[i] == 'l') {
            control = (VerifyText(textImport, themes[1], i, 1) == 1) ? 2: 0;
            i += themes[1].size() - 1;
        }
        else i++;
    }
    return control;
}

string replaceTheme(string Original, int themeInput) {

    int i, j = i = 0, theme = themeInput;
    string str = Original;
    string newStr;
    
    while (i < str.size()) {
        if (VerifyText(str, themes[theme], i, 0) == 1) {
            newStr += themes[(theme + 1) % 2];
            i += themes[theme].length();
        } else {
            newStr.push_back(str[i]);
            i++;
        } 
    }
    
    return newStr;
}

int ReadFile() {
    string linea;
    string newLine;
    ifstream file(path);
    
    

    if (!file.is_open()) {
        return -1;
    }
    
    while (getline(file, linea)) {
        int theme = checkTheme(linea);
        bool checkLine = theme == -1 ? 0 : 1;
        
        if (checkLine) {
            newLine = replaceTheme(linea, theme == 1 ? 0 : 1);
            text += newLine;
        } else {
            text += linea;
        }
        text.push_back('\n');
    }
    
    file.close();
    return 0;
}

int WriteFile() {
    ofstream file;
    
    file.open(path, fstream::out);
    
    if (!file.is_open()) {
        return -1;
    }
    
    file << text;

    file.close();
    return 0;
}

int main () {
    
    int ReadStatus = ReadFile();
    
    if (ReadStatus == -1) {
        cout << "hubo un error y no se pudo abrir el archivo" << endl;
        return -1;
    }
    
    int writeStatus = WriteFile();
    
    if (ReadStatus == -1) {
        cout << "hubo un error y no se pudo abrir el archivo" << endl;
        return -1;
    }

    cout << "Todo Ok";

    return 0;
}