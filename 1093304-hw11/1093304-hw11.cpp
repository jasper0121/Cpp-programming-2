#include<iostream>
#include<string>
#include"MakeReservation.h" //包含AvailTableDatabase.h, ReservationDatabase.h, AvailTable.h, Reservation.h, Date.h
#include"ReservationInquiry.h"
using namespace std;

int displayMainMenu();
void performReservations(AvailTableDatabase&, ReservationDatabase&);

int main()
{
	ReservationDatabase reservationDatabase; //含所有訂單的資料庫
	AvailTableDatabase availTableDatabase; //含30天桌子的資料庫
	cout << "Welcome to Hi-Lai Harbour Taoyuan Location!\n\n";
	performReservations(availTableDatabase, reservationDatabase); //執行訂桌
	cout << "\n";
	system("pause");
	return 0;
}

int displayMainMenu()
{
	string choice;
	cout << "1 - Book a Table\n2 - My Bookings\n3 - End\n\nEnter your choice: (1~3): ";
	getline(cin, choice);
	return (choice.size() == 1 && ('1' <= choice[0] && choice[0] <= '3')) ? choice[0] - '0' : -1; //若輸入正確則回傳選擇，否則回傳-1
}

void performReservations(AvailTableDatabase& availTableDatabase, ReservationDatabase& reservationDatabase)
{
	MakeReservation book_table; //訂桌
	ReservationInquiry reservationInquiry; //查詢
	while (true)
	{
		int choice = displayMainMenu(); //顯示並選擇菜單(含防呆)
		switch (choice)
		{
		case 1:
			book_table.execute(availTableDatabase, reservationDatabase); //執行訂桌
			break;
		case 2:
			reservationInquiry.execute(availTableDatabase, reservationDatabase); //執行訂單查詢
			break;
		case 3:
			return; //結束訂桌
		default:
			cout << "\nInput error. Please try again\n\n"; //choice == -1
			break;
		}
	}
}