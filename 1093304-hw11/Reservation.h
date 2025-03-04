#ifndef RESERVATION_H
#define RESERVATION_H

#include"AvailTable.h" //包含Date
using namespace std;

class Reservation
{
public:
	int getCustomers() const; //回傳客人數
	Date getDate() const; //回傳日期(包含年、月、日)
	int getTimeCode() const; //回傳時間代碼
	string getPassword() const; //回傳密碼
	string getReservationNumber() const; //回傳訂單編號
	string getStringTime(const int&) const; //將時間代碼轉換成相對應的時間
	void inputNumCustomers(const int&); //紀錄客人數
	void inputDate(const AvailTable&); //將availTable裡的日期記錄在訂單上
	void inputTimeCode(const int&); //紀錄時間代碼
	void inputPersonalInfo(); //輸入個資(含防呆)
	void showReservation() const; //顯示此次的訂桌資訊
private:
	int numCustomers = 0;
	Date date = Date();
	int time = 0;
	char name[8] = "";
	char mobileNumber[12] = "";
	char email[40] = "";
	char password[12] = "";
	char reservationNumber[12] = "";
};

#endif