#include <iostream>

using namespace std;


string themes[2] = {"mocha", "latte"};

// return 1: themeMocha, return 2: themeLatte, return 0: control

bool VerifyText (string verification, string Findtext, int initial, int init) {
    bool flag = 1;
    if (initial + Findtext.size() > verification.size()) return 0;
    for (int i = init; i < Findtext.size(); i++) {
        if (verification[initial + i] != Findtext[i]) flag = 0;
    }
    return flag;
}
int checkTheme(string textImport) {
    int control;
    int i = 0, j;
    while(i < textImport.size()) {
        if (textImport[i] == 'm') {
            control =  VerifyText(textImport, themes[0], i, 1) == 1 ? 1: 0;
            i += themes[0].size() - 1;
        }
        else if (textImport[i] == 'l') {
            control =  VerifyText(textImport, themes[1], i, 1) == 2 ? 1: 0;
            i += themes[1].size() - 1;
        }
        else i++;
    }
    return control;
}

int main () {
    int defineTheme;
    int i, j = i = 0;
    string import = "@import \"colors/mocha.scss\";";
    string newImport;
    int theme = checkTheme(import);
    defineTheme = theme == 1 ? 0 : 1;

    cout << import << endl;

    while (i < import.size()) {
        if (VerifyText(import, themes[defineTheme], i, 0) == 1) {
            newImport += themes[(defineTheme + 1) % 2];
            i += themes[defineTheme].length();
        } else{
            newImport.push_back(import[i]);
            i++;
        } 
    }

    cout << newImport << endl;

    return 0;
}