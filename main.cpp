#include "QFloat.h"
#include <fstream>

char operatorArray[10] = {'+', '-', '*', '/', '&', '|', '^', '~', '<', '>'};

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    while(1){
        string a, b, c, d;
        bool flag = false;
        cin >> a >> b >> c;
        if (a == "") break;
        for (int i = 0; i < 10; i++)
            if (c[0] == operatorArray[i]){
                flag = true;
                break;
            }
        if (flag){
            cin >> d;
            QFloat temp1, temp2, temp;
            if (a == "2"){
                temp1 = ConvertBinStringToQFloat(b);
                temp2 = ConvertBinStringToQFloat(d);
            } else {
                temp1 = ConvertDecStringToQFloat(b);
                temp2 = ConvertDecStringToQFloat(d);
            }
            if (c[0] == '+') temp = temp1 + temp2;
            if (c[0] == '-') temp = temp1 - temp2;
            if (c[0] == '*') temp = temp1 * temp2;
            if (c[0] == '/') temp = temp1 / temp2;
            if (a == "2")
                cout << ConvertQFloatToBinString(temp);
            else
                cout << ConvertQFloatToDecString(temp);
        } else {
            if (a == "2"){
                QFloat temp = ConvertBinStringToQFloat(c);
                cout << ConvertQFloatToDecString(temp);
            } else {
                QFloat temp = ConvertDecStringToQFloat(c);
                cout << ConvertQFloatToBinString(temp);
            }
        }
        cout << endl;
    }
    return 0;
}
