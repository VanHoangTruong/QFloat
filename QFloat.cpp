#include"QFloat.h"

// Khởi tạo mặc định bằng 0
QFloat::QFloat()
{
	for (int i = 0; i < 16; i++)
		this->data[i] = 0;
}

// Khởi tạo QFloat từ QFloat khác
QFloat::QFloat(const QFloat &p)
{
	for (int i = 0; i < 16; i++)
		this->data[i] = p.data[i];
}

// Hàm tạo QFloat từ mảng unsigned char[16]
QFloat::QFloat(unsigned char init_data[16])
{
	for (int i = 0; i < 16; i++)
		this->data[i] = init_data[i];
}

// Hàm tách lấy phần mũ và phần trị
void QFloat::separate(int &pow)
{
	pow = (int)data[0] * 256 + (int)data[1];
	this->data[0] = 1;
	this->data[1] = 0;
}

// operator =
QFloat QFloat::operator = (const QFloat &p) {
	for (int i = 0; i < 16; i++)
		this->data[i] = p.data[i];
		return *this;
}

// Operator +
QFloat QFloat::operator + (const QFloat &p)
{
    bool sign = 0 ;
    int  pow1 = 0, pow2 = 0;
	QFloat q(p);

	// Số hạng 1 dương
	if((int)this->data[0] < 128)
    {
        // số hạng 2 âm
        if((int)q.data[0] > 128)
        {
            QFloat ans;
            q.data[0] = q.data[0] - 128;
            ans = *this - q;
            return ans;
        }
    }
    // số hạng 1 âm
    else
    {
        // số hạng 2 dương
        if((int)q.data[0] < 128)
        {
            QFloat ans;
            this->data[0] = this->data[0] - 128;
            ans = q - *this;
            return ans;
        }
        // số trừ âm
        else {
            q.data[0]= q.data[0] - 128;
            this->data[0] = this->data[0]-128;
            sign = 1;
        }
    }

	this->separate(pow1);
	q.separate(pow2);

	QInt a(this->data);

	QInt b(q.data);
	int tmp = pow1 - pow2;
	int pow = 0;
	if (pow1 > pow2) pow = pow1;
	else pow = pow2;
	QInt ans_int;

	if (tmp < 0)
	{
		a = a >> 1;
        a.data[1]=0;
		a.data[2] = a.data[2] | 128;
		b = b >> 1;
		b.data[2] = b.data[2] | 128;
		a = a >> (-tmp  );
		ans_int = a + b;
		if ((ans_int.data[1]%2) == 1) {
			pow++;
			ans_int= ans_int >> 1;
		}
		ans_int= ans_int << 1;
	}
	else if (tmp > 0)
	{
		b = b >> 1;
		b.data[1]=0;
		b.data[2] = b.data[2] | 128;
		a = a >> 1;
		a.data[2] = a.data[2] | 128;
		b = b >> (tmp );
		ans_int = a + b;
		if ((ans_int.data[1]%2) == 1) {
			pow++;
			ans_int= ans_int >> 1;
		}
		ans_int= ans_int << 1;
	}
	else
	{
	    a.data[0]+=1;
	    a = a >> 1;
	    a.data[1]=0;
		a.data[2] = a.data[2] | 128;
		b.data[0]+=1;
		b = b >> 1;
		b.data[1]=0;
		b.data[2] = b.data[2] | 128;
		ans_int = a + b;
		if ((ans_int.data[1]%2) == 1) {
			pow++;
			ans_int.data[1]=0;
			ans_int= ans_int >> 1;
		}
		ans_int= ans_int << 1;
	};
    ans_int.data[1]= pow % 256;
    ans_int.data[0]= pow / 256;
    if(sign) ans_int.data[0] = ans_int.data[0] + 128;
	QFloat ans_float(ans_int.data);
	return ans_float;
}

// Operator -
QFloat QFloat::operator - (const QFloat &p)
{
    bool sign = 0;
	int  pow1 = 0, pow2 = 0;
	QFloat q(p);

	// Số hạng 1 dương
	if((int)this->data[0] < 128)
    {
        // số hạng 2 âm
        if((int)q.data[0] > 128)
        {
            q.data[0] = q.data[0] - 128;
            return *this + q;
        }
        // số hạng 2 dương
        else{
            this->separate(pow1);
            q.separate(pow2);

            QInt a(this->data);
            QInt b(q.data);

            int tmp = pow1 - pow2;
            int pow = 0;
            if (pow1 > pow2) pow = pow1;
            else pow = pow2;
            QInt ans_int;

            if (tmp > 0)
            {
                a.data[1]=1;
                a.data[0]=0;
                b.data[1]=1;
                b.data[0]=0;
                b = b >> (tmp);

                ans_int = a - b;
                if((int)ans_int.data[1] == 0)
                {
                    while(ConvertQIntToBinString(ans_int).length() < 112)
                    {
                        ans_int = ans_int << 1;
                        pow --;
                    }
                    ans_int = ans_int << 1;
                    pow --;
                }
            }
            else
            if (tmp == 0) {
                a.data[1]=1;
                a.data[0]=0;
                b.data[1]=1;
                b.data[0]=0;
                ans_int = a - b;
                int temp = 0;
                temp = 113 - ConvertQIntToBinString(ans_int).length();
                if(ConvertQIntToBinString(ans_int).length() == 0)
                    {
                        temp = pow;
                    }
                ans_int = ans_int << temp;
                pow = pow - temp;
            } else {
                sign =1;
                a.data[1]=1;
                a.data[0]=0;
                b.data[1]=1;
                b.data[0]=0;
                a = a >> (-tmp);
                ans_int = b - a;
                if((int)ans_int.data[1] == 0)
                {
                    ans_int = ans_int << 1;
                    pow --;
                }
    }
    ans_int.data[1]= pow % 256;
    ans_int.data[0]= pow / 256;
    if (sign) ans_int.data[0] = ans_int.data[0] + 128;
	QFloat ans_float(ans_int.data);
	return ans_float;
        }
    }
    // số hạng 1 âm
    else
    {
        // số hạng 2 dương
        if((int)q.data[0] < 128)
        {
            this->data[0] = this->data[0] - 128;
            QFloat ans = *this + q;
            ans.data[0] += 128;
            return ans;
        }
        // số trừ âm
        else {
            q.data[0]= q.data[0] - 128;
            return *this + q;
        }
    }
}

// Operator *
QFloat QFloat::operator * (const QFloat &p)
{
    int sign = 0;
	QFloat q = p;

	if((int)this->data[0] > 128)
       {
           sign = (sign + 1)%2;
           this->data[0] -=128;
       }
    if((int)q.data[0] > 128)
       {
           sign = (sign + 1)%2;
           q.data[0] -=128;
       }

    int  pow1, pow2;
	this->separate(pow1);
	q.separate(pow2);
	QInt a(this->data);
	QInt b(q.data);

	a.data[1]=1;
    a.data[0]=0;
    b.data[1]=1;
    b.data[0]=0;

    int pow = pow1 + pow2 - 16383;
    int tmp;
    if(pow1 > pow2)
    {
        b = b >>( pow1 - pow2);
        tmp = pow1-pow2;
    }
    else
    {
        a = a >> pow2 - pow1;
        tmp = pow2-pow1;
    }
    a = a >> 50;
    b = b >> 50;
    QInt ans_int = a*b;
    if(ConvertQIntToBinString(ans_int).length() == (126 - tmp))
    {
        pow ++;
        if(tmp < 13) ans_int = ans_int >> 13 - tmp;
        else ans_int = ans_int << tmp - 13;
    }
    else
    {
        if(tmp < 12) ans_int = ans_int >> 12 - tmp;
        else ans_int = ans_int << tmp - 12;
    }
    ans_int.data[1] = 0;
    ans_int.data[1] = pow % 256;
    ans_int.data[0] = pow / 256;
    if(sign) ans_int.data[0] = ans_int.data[0] + 128;
    QFloat ans_float(ans_int.data);
    return ans_float;

}

// Operator /
QFloat QFloat::operator / (const QFloat &p)
{
    int sign = 0;
	QFloat q = p;
    // Xét dấu
	if((int)this->data[0] > 128)
       {
           sign = (sign + 1)%2;
           this->data[0] -=128;
       }
    if((int)q.data[0] > 128)
       {
           sign = (sign + 1)%2;
           q.data[0] -=128;
       }
    // Tách mũ và phần trị
	int  pow1, pow2;
	this->separate(pow1);
	q.separate(pow2);
	QInt a(this->data);
	QInt b(q.data);
    // Thêm bit 1 vào đầu mỗi số để hoàn thiện số
	a.data[1]=1;
    a.data[0]=0;
    b.data[1]=1;
    b.data[0]=0;
    // Số mũ ban đầu
	int pow = pow1 - pow2 + 16383;
    if(pow1 > pow2)
    {
        b = b >>( pow1 - pow2);

        // Lưu kết quả
        string bit_dec = "";
        QInt tmp = a / b ;

        if(pow1 - pow2 == ConvertQIntToBinString(tmp).length())
            pow--;

        while(bit_dec.length() < 113)
        {
            tmp = a / b;
            if(ConvertQIntToBinString(tmp).length() == 0)
            {
                bit_dec.insert(bit_dec.length(),"0");
            }
            while(bit_dec[0]=='0')
                bit_dec.erase(0,1);
            bit_dec.insert(bit_dec.length(),ConvertQIntToBinString(tmp));
            a = a - b * tmp;
            a = a << 1;
        }
        QInt ans_int = ConvertBinStringToQInt(bit_dec);

        ans_int.data[1]= pow % 256;
        ans_int.data[0]= pow / 256;
        if(sign) ans_int.data[0] = ans_int.data[0] + 128;
        QFloat ans_float(ans_int.data);
        return ans_float;
    }
    else
    {
         b = b >>( pow2 - pow1 + 1);

        // Lưu kết quả
        string bit_dec = "";
        QInt tmp = a / b ;
        if(pow2 - pow1 == ConvertQIntToBinString(tmp).length() - 1 )
            pow --;

        while(bit_dec.length() < 113)
        {
            tmp = a / b;
            if(ConvertQIntToBinString(tmp).length() == 0)
            {
                bit_dec.insert(bit_dec.length(),"0");
            }
            while(bit_dec[0]=='0')
                bit_dec.erase(0,1);
            bit_dec.insert(bit_dec.length(),ConvertQIntToBinString(tmp));
            a = a - b * tmp;
            a = a << 1;
        }
        QInt ans_int = ConvertBinStringToQInt(bit_dec);

        ans_int.data[1]= pow % 256;
        ans_int.data[0]= pow / 256;
        if(sign) ans_int.data[0] = ans_int.data[0] + 128;
        QFloat ans_float(ans_int.data);
        return ans_float;
    }

}

// hàm chuyển số thực sang kiểu QFloat
QFloat ConvertDecStringToQFloat(string input){
    bool sign = 0;
    if(input[0] == '-') {
            sign = 1;
            input.erase(0,1);
    }
    int inputLen = (int)input.length();
    string Int = "", Dec = "";
    int i = 0;
    for (; i < inputLen; i++)
        if (input[i] != '.') Int = Int + input[i];
            else break;
    for (i++; i < inputLen; i++)
        Dec = Dec + input[i];
    QInt a = ConvertDecStringToQInt(Int);
    string bit_int = ConvertQIntToBinString(a);
    if (bit_int == "") bit_int = "0";
    int count = 112;
    string bit_dec = "";
    while (count--) {
        string temp = mulDecStringWithTwo(Dec);
        if (temp.length() > Dec.length()){
            bit_dec = bit_dec + '1';
            temp.erase(0, 1);
        } else bit_dec = bit_dec + '0';
        Dec = temp;
        bool flag = 0;
        for (int i = 0; i < Dec.length(); i++)
            if (Dec[i] != '0') flag = 1;
        if (!flag) break;
    }

    int pow = 0;
    if (bit_int.length() > 1){
        pow = (int)bit_int.length() - 1;
        bit_int.erase(0, 1);
        bit_dec = bit_int + bit_dec;
    } else
        if (bit_int.length() == 1 && bit_int == "1"){
            pow = 0;
        } else {
            while (1){
                if (bit_dec[0] == '1') {
                    bit_dec.erase(0, 1);
                    pow--;
                    break;
                }
                pow--;
                bit_dec.erase(0, 1);
            }
        }
    while (bit_dec.length() < 112)
        bit_dec = bit_dec + '0';
    while (bit_dec.length() > 112)
        bit_dec.erase(bit_dec.length() - 1, 1);

    a = ConvertBinStringToQInt(bit_dec);
    pow += 16383;
    a.data[1]= pow % 256;
    a.data[0]= pow / 256;
    if(sign) a.data[0] = a.data[0] + 128 ;
    QFloat b(a.data);
    return b;
}

// hàm chuyển đổi từ QFloat sang chuỗi số thực
string ConvertQFloatToDecString(QFloat input){
    QInt a(input.data);
    if(ConvertQIntToBinString(a).length()==0)
        return "0";
	bool sign = ((int)input.data[0] >> 7) & 1;
	int pow = (((int)input.data[0] & 127) * 256 + (int)input.data[1]) - 16383;
	input.data[0] = input.data[1] = 0;
	string str_bit = ConvertQIntToBinString(QInt(input.data));
    while (str_bit.length() < 112)
            str_bit = '0' + str_bit;
    str_bit = '1' + str_bit;

	string bit_int = "";
	string bit_dec = "";

	if (pow > 0) {
		bit_int = str_bit.substr(0,pow + 1);
		str_bit.erase(0, pow+1);
		bit_dec = str_bit;
	} else
		if (pow == 0){
			bit_int = "1";
			str_bit.erase(0, 1);
			bit_dec = str_bit;
		} else {
			bit_int = "0";
			string add = "";
            while(pow++ < -1)
				add = add + '0';
			bit_dec = add + str_bit;
		}
	string ans = ConvertQIntToDecString(ConvertBinStringToQInt(bit_int));

	string temp = "5";
	string res = "0";
	for (int i = 0; i < bit_dec.length(); i++){
        if (bit_dec[i] == '1')
            res = addTowDecString(res, temp);
        temp = mulDecStringWithFive(temp, i + 2);
        while (res.length() < temp.length()) res = res + '0';
	}
	while (res[res.length() - 1] == '0' && res.length() > 1)
        res.erase(res.length() - 1, 1);
    if(sign) return '-' + ans + '.' + res;
	return ans + '.' + res;
}

// hàm chuyển đổi từ chuỗi nhị phân sang QFloat
QFloat ConvertBinStringToQFloat(string input){
    QInt temp = ConvertBinStringToQInt(input);
    return QFloat(temp.data);
}

// hàm chuyển đổi từ QFloat sang chuỗi nhị phân
string ConvertQFloatToBinString(QFloat input){
    QInt temp = QInt(input.data);
    string ans = ConvertQIntToBinString(temp);
    while (ans.length() < 128) ans = '0' + ans;
    return ans;
}

