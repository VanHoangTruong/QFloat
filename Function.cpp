#include "Function.h"

// hàm trả về chuỗi kết quả khi chia chuỗi ở dạng thập phân cho 2
// ví dụ divDecStringByTwo("123") = "61"
string divDecStringByTwo(string input){
    if (input.length() == 0) return "0";
    if (input == "1" || input == "0") return "0";

    string ans = "";
    int curDigit = 0;
    int curPos = 0;
    int lenInput = (int)input.length();

    while (curPos < lenInput){
        curDigit = curDigit * 10 + (input[curPos] - '0');
        curPos++;
        if (curDigit >= 2) {
            ans = ans + (char)(curDigit / 2 + '0');
            curDigit = curDigit % 2;
        } else
            if (curPos - 1 != 0) ans = ans + '0';
    }
    return ans;
}

// hàm trả về chuỗi kết quả khi nhân chuỗi ở dạng thập phân với 2
// ví dụ: mulDecStringWithTwo("12") = "24"
string mulDecStringWithTwo(string input){
    string ans = "";
    int lenInput = (int)input.length();

    int mem = 0;

    for (int i = lenInput - 1; i >= 0; i--)
    {
        int temp = (int)(input[i] - '0') * 2 + mem;
        ans = (char)(temp % 10 + '0') + ans;
        mem = temp / 10;
    }

    if (mem) ans = (char)(mem + '0') + ans;
    return ans;
}

// hàm trả về chuỗi kết quả khi cộng hai chuỗi biểu diễn ở dạng thập phân
// ví dụ: addTowDecString("123", "77") = "200"
string addTowDecString(string a, string b){
    if (a.length() < b.length()) swap(a, b);

    int aLen = (int)a.length(), bLen = (int)b.length();
    string ans = "";
    int mem = 0;

    for (int i = 0; i < bLen; i++)
    {
        int temp = b[bLen - i - 1] - '0' + a[aLen - i - 1] - '0' + mem;
        ans = (char)(temp % 10 + '0') + ans;
        mem = temp / 10;
    }

    for (int i = 0; i < aLen - bLen; i++)
    {
        int temp = a[aLen - bLen - i - 1] - '0' + mem;
        ans = (char)(temp % 10 + '0') + ans;
        mem = mem / 10;
    }

    if (mem) ans = '1' + ans;
    return ans;
}

// hàm trả về chuỗi kết quả khi nhân chuỗi ở dạng thập phân với 5
//với định dạng len - ans.length() số không phía trước
// ví dụ: mulDecStringWithFive("11", 0) = "55"
string mulDecStringWithFive(string input, int len){
    string ans = "";
    int lenInput = (int)input.length();

    int mem = 0;

    for (int i = lenInput - 1; i >= 0; i--)
    {
        int temp = (int)(input[i] - '0') * 5 + mem;
        ans = (char)(temp % 10 + '0') + ans;
        mem = temp / 10;
    }

    if (mem) ans = (char)(mem + '0') + ans;
    string add = "";
    int ansLen = len - ans.length();
    for (int i = 0; i < ansLen; i++) add = add + '0';
    return add + ans;
}
