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
		if (availTableDatabase.availableTables(numCustomers, currentDate + num) == false) //�Y�ӤѦU�ɬq�ҿ諸�ู�Ҥw�Q�w�q
		{
			continue; //�h�L�k�A��ܸӤѪ��ู�A�G���L�X�Ӥ��
		}

		if (counter % 4 == 0) //�C���4�Ӥ���h����
		{
			counter = 0;
			cout << endl;
		}

		cout << setfill(' ') << setw(2) << num << ". " << currentDate + num << "   "; //�L�X�~���
		counter++; //������e�Ӧ�w�L�X�X�Ӥ��
	}

	int choice;
	do //���b�A�Y��J���~�ο�ܤw�����ู�h���s��J
	{
		cout << "\n?";
	} while ((choice = inputAnInteger(1, 30)) == -1 || availTableDatabase.availableTables(numCustomers, currentDate + choice) == false);

	date = currentDate + choice; //�����ҿ諸���
}

// choose a time
void MakeReservation::chooseTime(int& timeCode, Date date, int numCustomers)
{
	const string time[4]{ "", "11:30","14:30" ,"17:30" };
	cout << "\nChoose a time:";
	for (int pos = 1; pos <= 3; pos++) //��ɶ�
	{
		if (availTableDatabase.availableTables(numCustomers, date, pos) == false) //�Y�Ӯɬq�Ӯู�w�q�w���A�h�Ӯɬq�����
		{
			continue;
		}

		cout << "\n" << pos << ". " << time[pos];
	}

	do //���b�A�Y��J���~�ο�ܤw�����ู�h���s��J
	{
		cout << "\n? ";
	} while ((timeCode = inputAnInteger(1, 3)) == -1 || availTableDatabase.availableTables(numCustomers, date, timeCode) == false);
}