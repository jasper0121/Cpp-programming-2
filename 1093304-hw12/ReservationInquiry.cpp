#include <iostream>
#include <string>
using namespace::std;

#include "ReservationInquiry.h"

extern int inputAnInteger(int begin, int end);

ReservationInquiry::ReservationInquiry(ReservationDatabase& theReservationDatabase,
	AvailTableDatabase& theAvailTableDatabase)
	: reservationDatabase(theReservationDatabase),
	availTableDatabase(theAvailTableDatabase)
{
}

// reservation inquiry
void ReservationInquiry::execute()
{
	if (reservationDatabase.empty())
	{
		cout << "\nNo reservations!\n";
		return;
	}

	string reservationNumber;
	string password;
	cout << "\nEnter reservation number: ";
	getline(cin, reservationNumber);
	if (reservationDatabase.exist(reservationNumber)) //若reservationNumber存在
	{
		cout << "\nEnter reservation password: ";
		getline(cin, password);
		if (reservationDatabase.legal(reservationNumber, password)) //若reservationNumber和password皆正確
		{
			cout << endl;
			reservationDatabase.displayReservationInfo(reservationNumber); //則顯示訂桌資訊

			string choice;
			while (true) //防呆
			{
				cout << "\nCancel this reservation? ( y/n ) ";
				getline(cin, choice);
				if (choice == "y" || choice == "n") //若輸入不是y或n則繼續在迴圈內
				{
					if (choice == "y") //若輸入y
					{
						int numCustomers = reservationDatabase.getNumCustomers(reservationNumber); //紀錄客人數
						Date date = reservationDatabase.getDate(reservationNumber); //紀錄日期
						int timeCode = reservationDatabase.getTime(reservationNumber); //紀錄時間代碼
						availTableDatabase.increaseAvailTables(numCustomers, date, timeCode); //釋出桌子
						reservationDatabase.cancelReservation(reservationNumber); //刪除訂單
						cout << "\nThis reservation has been cancelled.\n";
					}

					return;
				}
			}
		}
		else
		{
			cout << "\nPassword error!\n";
		}

		return;
	}

	cout << "\nNo reservations with this reservation number!\n";
}