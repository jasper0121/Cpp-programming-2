#include <iostream>
#include <string>
#include <ctime>
using namespace::std;

#include "MakeReservation.h"    // MakeReservation class definition
#include "ReservationInquiry.h" // ReservationInquiry class definition

int inputAnInteger(int begin, int end); // input an integer in the range [ begin, end ]
Date computeCurrentDate(); // compute current date
bool leapYear(int year); // if the year is a leap year, return true; otherwise, return false

int main()
{
	cout << "Welcome to Hi-Lai Harbour Taoyuan Location!\n";

	ReservationDatabase reservationDatabase; // reservation information database
	AvailTableDatabase availTableDatabase;   // available table information database

	MakeReservation makeReservation(reservationDatabase, availTableDatabase);
	ReservationInquiry reservationInquiry(reservationDatabase, availTableDatabase);

	bool userExited = false; // user has not chosen to exit
	int choice;

	// loop while user has not chosen option to exit system
	while (!userExited)
	{
		cout << "\n1 - Book a Table\n";
		cout << "2 - My Bookings\n";
		cout << "3 - End\n\n";

		do cout << "Enter your choice: (1~3): ";
		while ((choice = inputAnInteger(1, 3)) == -1);

		// decide how to proceed based on user's menu selection
		switch (choice)
		{
		case 1:
			makeReservation.execute(); // make reservation
			break;
		case 2:
			reservationInquiry.execute(); // reservation inquiry
			break;
		case 3: // user chose to exit
			userExited = true;
			cout << endl;
			break;
		default: // user did not enter an integer from 1-3
			cout << "\nIncorrect choice!" << endl;
		}
	}

	system("pause");
}

int inputAnInteger(int begin, int end) //��J�Ʀr�è��b
{
	int number = 0;
	string choice;
	getline(cin, choice);
	for (size_t pos = 0; pos < choice.size(); pos++)
	{
		if (choice.size() > 2 || !('0' <= choice[pos] && choice[pos] <= '9') || choice[0] == '\0')
		{
			return -1; //�Y��J���r > 2  || �D�Ʀr || �S����J�Ӫ�����enter�A�h�^��-1
		}
		else
		{
			number += (choice[pos + 1] != '\0') ? (choice[pos] - '0') * 10 : (choice[pos] - '0'); //�Nchar�ഫ��int
		}
	}

	return (begin <= number && number <= end) ? number : -1; //�Y��J�b�d�򤺫h�^�ǸӼơA�_�h�^��-1
}

Date computeCurrentDate() //��X��e�ɶ�(year�q1900�}�l�Amonth�q1�}�l�Aday�q0�}�l)
{
	Date today;
	tm structuredTime;
	time_t rawTime = time(0); //�q1970/1/1/00:00:00�ܤ��L�F�X��
	localtime_s(&structuredTime, &rawTime); //��X�ɶ�
	today.setDate(1900 + structuredTime.tm_year, 1 + structuredTime.tm_mon, 0 + structuredTime.tm_mday); //�]�w��e�ɶ�
	return today;
}

bool leapYear(int year)
{
	return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
}