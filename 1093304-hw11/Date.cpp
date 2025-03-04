#include<iostream>
#include"Date.h"

Date::Date() //constructor，算出當前時間
{
	tm structuredTime;
	time_t rawTime = time(0);
	localtime_s(&structuredTime, &rawTime);
	year += structuredTime.tm_year; //year從1900開始
	month += structuredTime.tm_mon; //month從1開始
	day += structuredTime.tm_mday; //day從0開始
}

int Date::getYear() const //回傳年
{
	return year;
}

int Date::getMonth() const //回傳月
{
	return month;
}

int Date::getDay() const //回傳日
{
	return day;
}

void Date::dayAddition() //日期 + 1
{
	const int days_per_month[13] = { 0, 31, ((leapYear()) ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; //訂好每個月的天數
	if ((++(day %= days_per_month[month])) == 1) //每次取當月總天數的餘數後，先 + 1再判斷若 == 1日
	{
		if ((++(month %= 12)) == 1) //每次取12的餘數，先 + 1後再判斷若 == 1月
		{
			year++; //則年 + 1
		}
	}
}

void Date::inputDate(const int& inputYear, const int& inputMonth, const int& inputDay) //紀錄日期
{
	year = inputYear;
	month = inputMonth;
	day = inputDay;
}

bool Date::leapYear() const //算出是否閏年
{
	return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}