#include "QInt.h"

class QFloat
{
public:
	unsigned char data[16];
	QFloat();
	QFloat(const QFloat &p);
	QFloat(unsigned char init_data[16]);
	void separate(int &pow);
	QFloat operator + (const QFloat &p);
	QFloat operator - (const QFloat &p);
	QFloat operator * (const QFloat &p);
	QFloat operator / (const QFloat &p);
	QFloat operator = (const QFloat &p);
};
QFloat ConvertDecStringToQFloat(string);
string ConvertQFloatToDecString(QFloat);

QFloat ConvertBinStringToQFloat(string);
string ConvertQFloatToBinString(QFloat);
