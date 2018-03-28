#include "QInt.h"

//constructor mặc định của class QInt - default constructor
QInt::QInt(){
    for (int i = 0; i < 16; i++)
        data[i] = 0;
}

//constructor có tham số của class QInt constructor with argument
QInt::QInt(unsigned char initData[16]){
    for (int i = 0; i < 16; i++)
        data[i] = initData[i];
}

//bật bit tại vị trí post của QInt lên 1
void QInt::onBit(int pos) {
    if (pos < 0 || pos > 127) return;
    int index = pos / 8;
    int bit = pos % 8;
    data[15 - index] = (int)data[15 - index] | (1 << bit);
}

bool QInt::getBit(int pos) const {
    if (pos < 0 || pos > 127) return 0;
    int index = pos / 8;
    int bit = pos % 8;
    return ((data[15 - index] >> bit) & 1);
}

//operator +  của class QInt
QInt QInt::operator + (const QInt &p){
    QInt ans;
    int mem = 0;
    for (int i = 0; i < 128; i++){
        int temp = mem + this->getBit(i) + p.getBit(i);
        if (temp % 2) ans.onBit(i);
        mem = temp / 2;
    }
    return ans;
}

//operator - trừ của class QInt
QInt QInt::operator - (const QInt &p){
    QInt ans;
    int mem = 0;
    for (int i = 0; i < 128; i++){
        int temp = - mem + this->getBit(i) - p.getBit(i);
        if (temp < 0) {
            temp += 2;
            mem = 1;
        } else mem = 0;
        if (temp % 2) ans.onBit(i);
    }
    return ans;
}

//operator * nhân của class QInt
QInt QInt::operator * (const QInt &p){
    QInt ans;
    QInt temp = *this;
    for (int i  = 0; i < 128; i++) {
        if (p.getBit(i)) ans = ans + temp;
        temp = temp << 1;
    }
    return ans;
}

//operator / chia của class QInt
QInt QInt::operator / (const QInt &input){
    bool sign1 = 0, sign2 = 0;
    QInt A;
    QInt Q = *this;
    QInt M = input;
    if ((Q.data[0] >> 7) & 1) {
        sign1 = 1;
        Q = (~Q) + 1;
    }
    if ((M.data[0] >> 7) & 1) {
        sign2 = 1;
        M = (~M) + 1;
    }
    int count = 128;
    while (count--){
        A = A << 1;
        if ((Q.data[0] >> 7) & 1) A = A + 1;
        Q = Q << 1;
        A = A - M;
        if ((A.data[0] >> 7) & 1){
            Q.data[15] &= 254;
            A = A + M;
        } else {
            Q.data[15] |= 1;
        }
    }
    if (sign1 ^ sign2) return (~Q) + 1;
    return Q;
}

//operator + cộng số kiểu QInt với số int của class QInt
QInt QInt::operator + (int p) {
    for (int i = 15; i >= 0; i--)
        if (data[i] == 255){
            data[i] = 0;
        } else {
            data[i] += 1;
            break;
        }
    return *this;
}

//operator - trừ số kiểu QInt cho số int của class QInt
QInt QInt::operator - (int p) {
    for (int i = 15; i >= 0; i--)
        if (data[i] == 0){
            data[i] = 255;
        } else {
            data[i] -= 1;
            break;
        }
    return *this;
}

//operator & and của class QInt
QInt QInt::operator & (QInt p){
    QInt ans;
    for (int i = 0; i < 128; i++)
        if (this->getBit(i) & p.getBit(i))
            ans.onBit(i);
    return ans;
}

//operator | or của class QInt
QInt QInt::operator | (QInt p){
    QInt ans;
    for (int i = 0; i < 128; i++)
        if (this->getBit(i) | p.getBit(i))
            ans.onBit(i);
    return ans;
}

//operator ^ xor của class QInt
QInt QInt::operator ^ (QInt p){
    QInt ans;
    for (int i = 0; i < 128; i++)
        if (this->getBit(i) ^ p.getBit(i))
            ans.onBit(i);
    return ans;
}

//operator ~ not của class QInt
QInt QInt::operator ~ (){
    QInt ans;
    for (int i = 0; i < 128; i++)
        if (!this->getBit(i))
            ans.onBit(i);
    return ans;
}

//operator << shift right của class QInt
QInt QInt::operator << (int p){
    QInt ans;
    for (int i = 0; i < 128; i++)
        if (this->getBit(i))
            ans.onBit(i + p);
    return ans;
}

//operator << shift right của class QInt
QInt QInt::operator >> (int p){
    QInt ans;
    for (int i = 0; i < 128; i++)
        if (this->getBit(i))
            ans.onBit(i - p);
    return ans;
}

// operator = của class QInt
QInt QInt::operator = (const QInt &p){
     for (int i = 0; i < 16; i++)
        data[i] = p.data[i];
    return *this;
}

//---------------------------------------------------------------------------------------------

// hàm xuất ra màn hình số QInt ở dạng nhị phân
void PrintQInt(QInt input){
    for (int i = 127; i > 0; i--)
        cout << input.getBit(i);
}

//hàm chuyển đổi số biểu diễn ở dạng chuỗi thập phân sang biểu diễn ở dạng QInt
QInt ConvertDecStringToQInt(string input){
    QInt ans;
    int countIndex = 0;
    bool sign = 0;
    if (input[0] == '-'){
        sign = 1;
        input.erase(0, 1);
    }
    while (input.length() > 0 && input != "0") {
        int lastDigit = (input[input.length() - 1] - '0');
        if (lastDigit % 2) ans.onBit(countIndex);
        countIndex++;
        input = divDecStringByTwo(input);
    }
    if (sign) return (~ans) + 1;
    return ans;
}

//hàm chuyển đổi số biểu diễn ở dạng chuỗi nhị phân sang biểu diễn ở dạng QInt
QInt ConvertBinStringToQInt(string input){
    QInt ans;
    int inputLen = (int)input.length();
    for (int i = inputLen - 1; i >= 0; i--)
        if (input[i] - '0') ans.onBit(inputLen - 1 - i);
    return ans;
}

//hàm chuyển đổi số biểu diễn ở dạng chuỗi thập lục phân sang biểu diễn ở dạng QInt
QInt ConvertHexStringToQInt(string input){
    unsigned char ans[16] = {0};
    int countAns = 15;
    int inputLen = (int)input.length();
    int curInt = 0;
    for (int i = inputLen - 1; i >= 0; i--){
        int curDigit;
        if (input[i] >= '0' && input[i] <= '9') curDigit = input[i] - '0';
        else curDigit = input[i] - 'A' + 10;
        if ((inputLen - i) % 2) curInt = curDigit;
        else {
            ans[countAns--] = curInt + (curDigit << 4);
            curInt = 0;
        }
    }
    ans[countAns] = curInt;
    return QInt(ans);
}

//hàm chuyển đổi số biểu diễn ở dạng QInt sang biểu diễn ở dạng chuỗi nhị phân
string ConvertQIntToBinString(QInt input){
    string ans = "";
    bool flag = false;
    for (int i = 0; i < 16; i++){
        int temp = input.data[i];
        for (int j = 7; j >= 0; j--){
            if (((temp >> j) & 1) != 0) flag = true;
            if (flag) ans = ans + (char)(((temp >> j) & 1) + '0');
        }
    }
    return ans;
}

//hàm chuyển đổi số biểu diễn ở dạng QInt sang biểu diễn ở dạng chuỗi thập lục phân
string ConvertQIntToHexString(QInt input){
    string ans = "";
    bool flag = false;
    for (int i = 0; i < 16; i++){
        int temp = input.data[i];
        if ((temp >> 4) != 0) flag = true;
        if (flag){
            int add = '0';
            if ((temp >> 4) > 9) add = 'A' - 10;
            ans = ans + (char)((temp >> 4) + add);
        }
        if ((temp % 16) != 0) flag = true;
        if (flag){
            int add = '0';
            if ((temp % 16) > 9) add = 'A' - 10;
            ans = ans + (char)((temp % 16) + add);
        }
    }
    return ans;
}

//hàm chuyển đổi số biểu diễn ở dạng QInt sang biểu diễn ở dạng chuỗi thập phân
string ConvertQIntToDecString(QInt input){
    string ans = "0";
    string curPow = "1";
    bool flag = 0;
    if ((input.data[0] >> 7) & 1) {
        input = ~(input - 1);
        flag = 1;
    }
    for (int i = 15; i >= 0; i--){
        int temp = input.data[i];
        for (int j = 0; j < 8; j++){
            if ((temp >> j) & 1) ans = addTowDecString(ans, curPow);
            curPow = mulDecStringWithTwo(curPow);
        }
    }
    if (flag) ans = '-' + ans;
    return ans;
}
