#ifndef DATE_H
#define DATE_H

using namespace std;

class Date
{
public:
	Date(); //constructor�A��X��e�ɶ�
	int getYear() const; //�^�Ǧ~
	int getMonth() const; //�^�Ǥ�
	int getDay() const; //�^�Ǥ�
	void dayAddition(); //��� + 1
	void inputDate(const int&, const int&, const int&); //�������
private:
	int year = 1900;
	int month = 1;
	int day = 0;
	bool leapYear() const; //��X�O�_�|�~
};

#endif