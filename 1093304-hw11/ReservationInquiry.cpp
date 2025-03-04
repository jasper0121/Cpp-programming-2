#include<iostream>
#include<string>
#include"ReservationInquiry.h"

void ReservationInquiry::execute(AvailTableDatabase& availTableDatabase, ReservationDatabase& reservationDatabase) const //查詢
{
	if (reservationDatabase.DatabaseSize() == 0) //若reservation資料庫中沒有任何訂單
	{
		cout << "\nNo reservations!\n\n";
	}
	else
	{
		string reservation_number;
		string password;
		cout << "\nEnter reservation number: ";
		getline(cin, reservation_number);
		for (int pos = 0; pos < reservationDatabase.DatabaseSize(); pos++)
		{
			if (reservation_number == reservationDatabase.getReservation(pos).getReservationNumber()) //若資料庫中有該筆訂單編號
			{
				cout << "\nEnter reservation password: ";
				getline(cin, password);
				if (password == reservationDatabase.getReservation(pos).getPassword()) //若密碼輸入正確
				{
					reservationDatabase.getReservation(pos).showReservation(); //則顯示訂桌資訊
					chooseCancel(availTableDatabase, reservationDatabase, pos); //再詢問是否刪除此筆訂單
				}
				else
				{
					cout << "\nPassword error!\n\n";
				}

				return;
			}
		}

		cout << "\nNo reservations with this reservation number!\n\n";
	}
}

//詢問是否刪除此筆訂單
void ReservationInquiry::chooseCancel(AvailTableDatabase& availTableDatabase, ReservationDatabase& reservationDatabase, const int& pos) const
{
	string choice;
	while (true) //防呆
	{
		cout << "\n\nCancel this reservation? ( y/n ) ";
		getline(cin, choice);
		if (choice == "y" || choice == "n") //若輸入不是y或n則繼續在迴圈內
		{
			if (choice == "y") //若輸入y
			{
				Date date = reservationDatabase.getReservation(pos).getDate(); //紀錄日期
				int timeCode = reservationDatabase.getReservation(pos).getTimeCode(); //紀錄時間代碼
				int tableType = getTableType(reservationDatabase.getReservation(pos).getCustomers()); //紀錄桌號(繼承getTableType)
				reservationDatabase.eraseReservation(pos); //刪除訂單
				availTableDatabase.cancelBook(date, timeCode, tableType); //取消訂位
				cout << "\nThis reservation has been cancelled.\n\n";
			}

			return;
		}
	}
}