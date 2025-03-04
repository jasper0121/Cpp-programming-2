#ifndef DATE_H
#define DATE_H

using namespace std;

class Date
{
public:
	Date(); //constructor，算出當前時間
	int getYear() const; //回傳年
	int getMonth() const; //回傳月
	int getDay() const; //回傳日
	void dayAddition(); //日期 + 1
	void inputDate(const int&, const int&, const int&); //紀錄日期
private:
	int year = 1900;
	int month = 1;
	int day = 0;
	bool leapYear() const; //算出是否閏年
};

#endif