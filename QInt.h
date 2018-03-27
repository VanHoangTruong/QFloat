#include <iostream>
#include "Function.h"

class QInt{
public:
    unsigned char data[16];

    //constructor mặc định của class QInt
    QInt();
    //constructor có tham số của class QInt
    QInt(unsigned char initData[16]);

    //operator + cộng 2 số kiểu QInt
    QInt operator + (const QInt &);

    //operator - trừ 2 số kiểu QInt
    QInt operator - (const QInt &);

    //operator * nhân 2 số kiểu QInt
    QInt operator * (const QInt &);

    //operator / chia 2 số kiểu QInt
    QInt operator / (const QInt &);

    QInt operator + (int p);

    QInt operator - (int p);

    // operator and QInt
    QInt operator & (QInt);

    // operator or QInt
    QInt operator | (QInt);

    // operator xor QInt
    QInt operator ^ (QInt);

    // operator not QInt
    QInt operator ~ ();

    // operator << QInt
    QInt operator << (int);

    // operator >> QInt
    QInt operator >> (int);

    QInt operator = (const QInt &);
};

string ConvertQIntToBinString(QInt);
string ConvertQIntToDecString(QInt);
string ConvertQIntToHexString(QInt);
QInt ConvertBinStringToQInt(string);
QInt ConvertDecStringToQInt(string);
QInt ConvertHexStringToQInt(string);
void PrintQInt(QInt);
