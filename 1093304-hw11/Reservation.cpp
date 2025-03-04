#include<iostream>
#include<iomanip>
#include"Reservation.h"

int Reservation::getCustomers() const //回傳客人數
{
	return numCustomers;
}

Date Reservation::getDate() const //回傳日期(包含年、月、日)
{
	return date;
}

int Reservation::getTimeCode() const //回傳時間代碼
{
	return time;
}

string Reservation::getPassword() const //回傳密碼
{
	return password;
}

string Reservation::getReservationNumber() const //回傳訂單編號
{
	return reservationNumber;
}

string Reservation::getStringTime(const int& timeCode) const //將時間代碼轉換成相對應的時間
{
	const string time[4]{ "","11:30" ,"14:30" , "17:30" };
	return time[timeCode];
}

void Reservation::inputNumCustomers(const int& customer) //紀錄客人數
{
	numCustomers = customer;
}

void Reservation::inputDate(const AvailTable& availTable) //將availTable裡的日期記錄在訂單上
{
	date.inputDate(availTable.getYear(), availTable.getMonth(), availTable.getDay());
}

void Reservation::inputTimeCode(const int& timeCode) //紀錄時間代碼
{
	time = timeCode;
}

void Reservation::inputPersonalInfo() //輸入個資(含防呆)
{
	do
	{
		cout << "\nEnter name: ";
		cin.getline(name, 8, '\n');
	} while (name[0] == '\0'); //姓名

	do
	{
		cout << "\nEnter mobile number: ";
		cin.getline(mobileNumber, 12, '\n');
	} while (mobileNumber[0] == '\0'); //電話

	do
	{
		cout << "\nEnter email address: ";
		cin.getline(email, 40, '\n');
	} while (email[0] == '\0'); //email

	do
	{
		cout << "\nEnter reservation password: ";
		cin.getline(password, 12, '\n');
	} while (password[0] == '\0'); //密碼

	for (int n = 0; n < 8; n++) //亂數產生訂單編號(固定8位數)
	{
		reservationNumber[n] = (rand() % 10 + '0'); //每次放入亂數的個位數(int轉char)
	}
}

void Reservation::showReservation() const //顯示此次的訂桌資訊
{
	cout << "\nMobile No.      Name          Date     Time                         Email    No of Customers    Password    Reservation No.\n"
		<< setfill(' ') << setw(10) << mobileNumber << setw(10) << name
		<< setw(8) << date.getYear() << "/" << setfill('0') << setw(2) << date.getMonth() << "/" << setw(2) << date.getDay()
		<< setfill(' ') << setw(9) << getStringTime(time) << setw(30) << email << setw(19) << numCustomers << setw(12) << password
		<< setw(19) << reservationNumber;
}