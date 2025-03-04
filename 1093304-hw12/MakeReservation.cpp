// MakeReservation.cpp
// Member-function definitions for class MakeReservation.
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "MakeReservation.h"     // MakeReservation class definition

extern int inputAnInteger(int begin, int end);
extern Date computeCurrentDate();

// MakeReservation constructor initializes base-class data members
MakeReservation::MakeReservation(ReservationDatabase& theReservationDatabase,
	AvailTableDatabase& theAvailTableDatabase)
	: reservationDatabase(theReservationDatabase),
	availTableDatabase(theAvailTableDatabase)
{
}

// make reservation
void MakeReservation::execute()
{
	int numCustomers;
	do {
		cout << "\nEnter the number of customers (1 - 7, 10 - 12): ";
		numCustomers = inputAnInteger(1, 12);
	} while (numCustomers == 8 || numCustomers == 9 || numCustomers == -1);

	Date currentDate = computeCurrentDate();

	Date date;
	chooseDate(date, currentDate, numCustomers);

	int timeCode;
	chooseTime(timeCode, date, numCustomers);

	cout << "\nEnter name: ";
	string name;
	cin >> name;

	cout << "\nEnter mobile number: ";
	string mobileNumber;
	cin >> mobileNumber;

	cout << "\nEnter email address: ";
	string email;
	cin >> email;

	cout << "\nEnter reservation password: ";
	string password;
	cin >> password;
	cin.ignore();

	string reservationNumber;
	for (int i = 0; i < 8; i++)
		reservationNumber.push_back(rand() % 10 + '0');

	Reservation newReservation(numCustomers, date, timeCode, name, mobileNumber,
		email, password, reservationNumber);

	cout << setfill(' ') << endl << setw(11) << "Mobile No." << setw(10) << "Name"
		<< setw(14) << "Date" << setw(9) << "Time" << setw(30) << "Email"
		<< setw(19) << "No of Customers" << setw(12) << "Password"
		<< setw(19) << "Reservation No." << endl;

	newReservation.displayReservationInfo();

	reservationDatabase.pushBack(newReservation);

	cout << "\nReservation Completed.\n";

	availTableDatabase.decreaseAvailTables(numCustomers, date, timeCode);
}

// choose a date
void MakeReservation::chooseDate(Date& date, Date currentDate, int numCustomers)
{
	cout << "\nChoose a date";
	for (int counter = 0, num = 1; num <= 30; num++)
	{
		if (availTableDatabase.availableTables(numCustomers, currentDate + num) == false) //若該天各時段所選的桌號皆已被預訂
		{
			continue; //則無法再選擇該天的桌號，故不印出該日期
		}

		if (counter % 4 == 0) //每顯示4個日期則換行
		{
			counter = 0;
			cout << endl;
		}

		cout << setfill(' ') << setw(2) << num << ". " << currentDate + num << "   "; //印出年月日
		counter++; //紀錄當前該行已印出幾個日期
	}

	int choice;
	do //防呆，若輸入錯誤或選擇已滿的桌號則重新輸入
	{
		cout << "\n?";
	} while ((choice = inputAnInteger(1, 30)) == -1 || availTableDatabase.availableTables(numCustomers, currentDate + choice) == false);

	date = currentDate + choice; //紀錄所選的日期
}

// choose a time
void MakeReservation::chooseTime(int& timeCode, Date date, int numCustomers)
{
	const string time[4]{ "", "11:30","14:30" ,"17:30" };
	cout << "\nChoose a time:";
	for (int pos = 1; pos <= 3; pos++) //選時間
	{
		if (availTableDatabase.availableTables(numCustomers, date, pos) == false) //若該時段該桌號預訂已滿，則該時段不顯示
		{
			continue;
		}

		cout << "\n" << pos << ". " << time[pos];
	}

	do //防呆，若輸入錯誤或選擇已滿的桌號則重新輸入
	{
		cout << "\n? ";
	} while ((timeCode = inputAnInteger(1, 3)) == -1 || availTableDatabase.availableTables(numCustomers, date, timeCode) == false);
}