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
	if (reservationDatabase.exist(reservationNumber)) //�YreservationNumber�s�b
	{
		cout << "\nEnter reservation password: ";
		getline(cin, password);
		if (reservationDatabase.legal(reservationNumber, password)) //�YreservationNumber�Mpassword�ҥ��T
		{
			cout << endl;
			reservationDatabase.displayReservationInfo(reservationNumber); //�h��ܭq���T

			string choice;
			while (true) //���b
			{
				cout << "\nCancel this reservation? ( y/n ) ";
				getline(cin, choice);
				if (choice == "y" || choice == "n") //�Y��J���Oy��n�h�~��b�j�餺
				{
					if (choice == "y") //�Y��Jy
					{
						int numCustomers = reservationDatabase.getNumCustomers(reservationNumber); //�����ȤH��
						Date date = reservationDatabase.getDate(reservationNumber); //�������
						int timeCode = reservationDatabase.getTime(reservationNumber); //�����ɶ��N�X
						availTableDatabase.increaseAvailTables(numCustomers, date, timeCode); //���X��l
						reservationDatabase.cancelReservation(reservationNumber); //�R���q��
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