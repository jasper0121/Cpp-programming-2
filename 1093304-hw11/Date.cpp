#include<iostream>
#include"Date.h"

Date::Date() //constructor�A��X��e�ɶ�
{
	tm structuredTime;
	time_t rawTime = time(0);
	localtime_s(&structuredTime, &rawTime);
	year += structuredTime.tm_year; //year�q1900�}�l
	month += structuredTime.tm_mon; //month�q1�}�l
	day += structuredTime.tm_mday; //day�q0�}�l
}

int Date::getYear() const //�^�Ǧ~
{
	return year;
}

int Date::getMonth() const //�^�Ǥ�
{
	return month;
}

int Date::getDay() const //�^�Ǥ�
{
	return day;
}

void Date::dayAddition() //��� + 1
{
	const int days_per_month[13] = { 0, 31, ((leapYear()) ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; //�q�n�C�Ӥ몺�Ѽ�
	if ((++(day %= days_per_month[month])) == 1) //�C��������`�Ѽƪ��l�ƫ�A�� + 1�A�P�_�Y == 1��
	{
		if ((++(month %= 12)) == 1) //�C����12���l�ơA�� + 1��A�P�_�Y == 1��
		{
			year++; //�h�~ + 1
		}
	}
}

void Date::inputDate(const int& inputYear, const int& inputMonth, const int& inputDay) //�������
{
	year = inputYear;
	month = inputMonth;
	day = inputDay;
}

bool Date::leapYear() const //��X�O�_�|�~
{
	return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}