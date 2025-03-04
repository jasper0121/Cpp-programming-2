// Date.cpp
// Date-function definitions for class Date.
#include <iostream>
#include <iomanip>
using namespace std;

#include "Date.h"

int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; // array of days per month

extern bool leapYear(int year);

Date::Date()
{
	year = 2000;
	month = 0;
	day = 0;
}

Date::Date(int y, int m, int d)
{
	setDate(y, m, d);
}

// const return avoids: ( a1 = a2 ) = a3
const Date& Date::operator=(const Date& right)
{
	if (&right != this) // avoid self-assignment
	{
		month = right.month;
		day = right.day;
		year = right.year;
	}

	return *this; // enables x = y = z, for example
} // end function operator=

void Date::setDate(int y, int m, int d)
{
	setYear(y);
	setMonth(m);
	setDay(d);
}

void Date::setYear(int y)
{
	year = (y >= 2000) ? y : 2000; // sets year
} // end function setYear

void Date::setMonth(int m)
{
	month = (m >= 1 && m <= 12) ? m : 1; // sets month
} // end function setMonth

void Date::setDay(int d)
{
	if (month == 2 && leapYear(year))
		day = (d >= 1 && d <= 29) ? d : 1;
	else
		day = (d >= 1 && d <= days[month]) ? d : 1;
} // end function setDay

int Date::getYear() const
{
	return year;
}

int Date::getMonth() const
{
	return month;
}

int Date::getDay() const
{
	return day;
}

bool Date::operator==(const Date& date2)
{
	return (year == date2.year && month == date2.month && day == date2.day);
}

bool Date::operator<(const Date& date2)
{
	if (year < date2.year)
		return true;
	if (year > date2.year)
		return false;

	if (month < date2.month)
		return true;
	if (month > date2.month)
		return false;

	if (day < date2.day)
		return true;

	return false;
}

bool Date::operator<=(const Date& date2)
{
	return (*this < date2 || *this == date2);
}

// if the year is a leap year, return true; otherwise, return false
bool Date::leapYear(int testYear) const
{
	if (testYear % 400 == 0 ||
		(testYear % 100 != 0 && testYear % 4 == 0))
		return true; // a leap year
	else
		return false; // not a leap year
} // end function leapYear

// return *this - date2 provided that *this > date2
int Date::operator-(const Date& date2)
{
	if (*this <= date2) //�Y��e����� <= date2�h�^��0
	{
		return 0;
	}
	else //��X2����U�۶Zdate2.year/date2.month/1���Ѽƨì۴�
	{
		if (leapYear(year)) //�Y���|�~�h2���29��
		{
			days[2] = 29;
		}

		size_t total_date2 = date2.day; //date2���`�Ѽ�(�Zdate2.month/1)
		size_t total_this = this->day; //*this���`�Ѽ�(�Zthis->month/1)
		for (int m = date2.month; m != this->month; (m %= 12)++) //�Ydate2.month != this->month
		{
			total_this += days[m]; //�htotal_this += 2�Ӥ���������Ѽ�
		}

		return (total_this - total_date2); //�^��2������ѼƮt
	}
}

Date Date::operator+(int numDays) //��e��� + numDays��
{
	if (leapYear(year)) //�Y���|�~�h2���29��
	{
		days[2] = 29;
	}

	Date date = *this; //��ldate == today
	if ((date.day += numDays) > days[month]) //�Y�Ѽƥ[�`�� > ���Ѽ�
	{
		date.day -= days[month]; //�ѼƬ۴�
		if ((++(date.month %= 12)) == 1) //�C����12���l�ơA�� + 1��A�P�_�Y == 1��
		{
			date.year++; //�h�~ + 1
		}
	}

	return date;
}

// overloaded output operator
ostream& operator<<(ostream& output, const Date& d)
{
	output << setw(4) << d.year << "/" << setfill('0') << setw(2) << d.month
		<< '/' << setw(2) << d.day;
	return output; // enables cascading
} // end function operator<<