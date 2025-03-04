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
	if (*this <= date2) //若當前的日期 <= date2則回傳0
	{
		return 0;
	}
	else //算出2日期各自距date2.year/date2.month/1的天數並相減
	{
		if (leapYear(year)) //若為閏年則2月改29天
		{
			days[2] = 29;
		}

		size_t total_date2 = date2.day; //date2的總天數(距date2.month/1)
		size_t total_this = this->day; //*this的總天數(距this->month/1)
		for (int m = date2.month; m != this->month; (m %= 12)++) //若date2.month != this->month
		{
			total_this += days[m]; //則total_this += 2個月份之間的天數
		}

		return (total_this - total_date2); //回傳2日期的天數差
	}
}

Date Date::operator+(int numDays) //當前日期 + numDays天
{
	if (leapYear(year)) //若為閏年則2月改29天
	{
		days[2] = 29;
	}

	Date date = *this; //初始date == today
	if ((date.day += numDays) > days[month]) //若天數加總後 > 當月天數
	{
		date.day -= days[month]; //天數相減
		if ((++(date.month %= 12)) == 1) //每次取12的餘數，先 + 1後再判斷若 == 1月
		{
			date.year++; //則年 + 1
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