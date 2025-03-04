#include<iostream>
#include<string>
#include"MakeReservation.h" //�]�tAvailTableDatabase.h, ReservationDatabase.h, AvailTable.h, Reservation.h, Date.h
#include"ReservationInquiry.h"
using namespace std;

int displayMainMenu();
void performReservations(AvailTableDatabase&, ReservationDatabase&);

int main()
{
	ReservationDatabase reservationDatabase; //�t�Ҧ��q�檺��Ʈw
	AvailTableDatabase availTableDatabase; //�t30�Ѯ�l����Ʈw
	cout << "Welcome to Hi-Lai Harbour Taoyuan Location!\n\n";
	performReservations(availTableDatabase, reservationDatabase); //����q��
	cout << "\n";
	system("pause");
	return 0;
}

int displayMainMenu()
{
	string choice;
	cout << "1 - Book a Table\n2 - My Bookings\n3 - End\n\nEnter your choice: (1~3): ";
	getline(cin, choice);
	return (choice.size() == 1 && ('1' <= choice[0] && choice[0] <= '3')) ? choice[0] - '0' : -1; //�Y��J���T�h�^�ǿ�ܡA�_�h�^��-1
}

void performReservations(AvailTableDatabase& availTableDatabase, ReservationDatabase& reservationDatabase)
{
	MakeReservation book_table; //�q��
	ReservationInquiry reservationInquiry; //�d��
	while (true)
	{
		int choice = displayMainMenu(); //��ܨÿ�ܵ��(�t���b)
		switch (choice)
		{
		case 1:
			book_table.execute(availTableDatabase, reservationDatabase); //����q��
			break;
		case 2:
			reservationInquiry.execute(availTableDatabase, reservationDatabase); //����q��d��
			break;
		case 3:
			return; //�����q��
		default:
			cout << "\nInput error. Please try again\n\n"; //choice == -1
			break;
		}
	}
}