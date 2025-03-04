#include<iostream>
#include<string>
#include"ReservationInquiry.h"

void ReservationInquiry::execute(AvailTableDatabase& availTableDatabase, ReservationDatabase& reservationDatabase) const //�d��
{
	if (reservationDatabase.DatabaseSize() == 0) //�Yreservation��Ʈw���S������q��
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
			if (reservation_number == reservationDatabase.getReservation(pos).getReservationNumber()) //�Y��Ʈw�����ӵ��q��s��
			{
				cout << "\nEnter reservation password: ";
				getline(cin, password);
				if (password == reservationDatabase.getReservation(pos).getPassword()) //�Y�K�X��J���T
				{
					reservationDatabase.getReservation(pos).showReservation(); //�h��ܭq���T
					chooseCancel(availTableDatabase, reservationDatabase, pos); //�A�߰ݬO�_�R�������q��
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

//�߰ݬO�_�R�������q��
void ReservationInquiry::chooseCancel(AvailTableDatabase& availTableDatabase, ReservationDatabase& reservationDatabase, const int& pos) const
{
	string choice;
	while (true) //���b
	{
		cout << "\n\nCancel this reservation? ( y/n ) ";
		getline(cin, choice);
		if (choice == "y" || choice == "n") //�Y��J���Oy��n�h�~��b�j�餺
		{
			if (choice == "y") //�Y��Jy
			{
				Date date = reservationDatabase.getReservation(pos).getDate(); //�������
				int timeCode = reservationDatabase.getReservation(pos).getTimeCode(); //�����ɶ��N�X
				int tableType = getTableType(reservationDatabase.getReservation(pos).getCustomers()); //�����ู(�~��getTableType)
				reservationDatabase.eraseReservation(pos); //�R���q��
				availTableDatabase.cancelBook(date, timeCode, tableType); //�����q��
				cout << "\nThis reservation has been cancelled.\n\n";
			}

			return;
		}
	}
}