#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace::std;

#include "ReservationDatabase.h" // ReservationDatabase class definition

extern Date computeCurrentDate();

// call loadReservations and removes outdated reservation informations
ReservationDatabase::ReservationDatabase() //constructor�AŪ�ɨçR���­q��
{
	loadReservations();

	Date today = computeCurrentDate(); //���Ѫ����
	vector<Reservation>::iterator eraseItr = reservations.begin(); //eraseItr���V�}�C���}�Y
	for (size_t pos = 0; pos < reservations.size(); )
	{
		if (reservations[pos].getDate() <= today) //�Y�{�s�b��Ʈw�����ӵ��q��L��
		{
			reservations.erase(eraseItr); //�R���q��
		}
		else //erase���U���V���Ӯ欰erase�e���U�@���ơA�Gerase�ᤣ++
		{
			pos++, eraseItr++; //�Y��e�Ӯ椣��erase�A�h���U�@���ˬd
		}
	}
}

// call storeReservations
ReservationDatabase::~ReservationDatabase()
{
	storeReservations();
}

bool ReservationDatabase::empty()
{
	return (reservations.size() == 0);
}

// returns true if there is a Reservation object containing specified reservationNumber
bool ReservationDatabase::exist(string reservationNumber) //�ˬdreservations�O�_�s�b
{
	for (int pos = 0; pos < reservations.size(); pos++)
	{
		if (reservations[pos].getReservationNumber() == reservationNumber)
		{
			return true;
		}
	}

	return false;
}

// returns true if there is a Reservation object containing specified reservationNumber and password
bool ReservationDatabase::legal(string reservationNumber, string password) //�ˬdreservations�Mpassword�O�_�s�b
{
	for (int pos = 0; pos < reservations.size(); pos++)
	{
		if (reservations[pos].getReservationNumber() == reservationNumber && reservations[pos].getPassword() == password)
		{
			return true;
		}
	}

	return false;
}

// returns numCustomers in the Reservation object containing specified reservationNumber
int ReservationDatabase::getNumCustomers(string reservationNumber)
{
	vector< Reservation >::iterator it = getReservation(reservationNumber);
	return it->getNumCustomers();
}

// returns date in the Reservation object containing specified reservationNumber
Date ReservationDatabase::getDate(string reservationNumber)
{
	vector< Reservation >::iterator it = getReservation(reservationNumber);
	return it->getDate();
}

// returns time in the Reservation object containing specified reservationNumber
int ReservationDatabase::getTime(string reservationNumber)
{
	vector< Reservation >::iterator it = getReservation(reservationNumber);
	return it->getTime();
}

// cancels the Reservation object containing specified reservationNumber,
void ReservationDatabase::cancelReservation(string reservationNumber)
{
	vector< Reservation >::iterator it = getReservation(reservationNumber);
	reservations.erase(it);
}

// for the Reservation object containing specified reservationNumber,
// displays all the reservation informations
void ReservationDatabase::displayReservationInfo(string reservationNumber)
{
	cout << setfill(' ') << setw(11) << "Mobile No." << setw(10) << "Name"
		<< setw(14) << "Date" << setw(9) << "Time" << setw(30) << "Email"
		<< setw(19) << "No of Customers" << setw(12) << "Password"
		<< setw(19) << "Reservation No." << endl;

	vector< Reservation >::iterator it = getReservation(reservationNumber);
	it->displayReservationInfo();
}

// adds newReservation at the end of reservations
void ReservationDatabase::pushBack(Reservation newReservation)
{
	reservations.push_back(newReservation);
}

// loads reservations from the file Reservations.dat
void ReservationDatabase::loadReservations() //Ū��
{
	ifstream inFile("Reservations.dat", ios::binary);

	if (!inFile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}

	for (Reservation data; inFile.read(reinterpret_cast<char*>(&data), sizeof(data)); reservations.push_back(data)); //�নchar��[�J��Ʈw

	inFile.close();
}

// stores reservations into the file Reservations.dat
void ReservationDatabase::storeReservations() //�g��
{
	ofstream outFile("Reservations.dat", ios::binary);

	for (size_t pos = 0; pos < reservations.size(); pos++) //�নconst char��g�Jdat��
	{
		outFile.write(reinterpret_cast<const char*>(&reservations[pos]), sizeof(reservations[pos]));
	}

	outFile.close();
}

// returns an iterator that points to the Reservation object containing specified reservationNumber
vector< Reservation >::iterator ReservationDatabase::getReservation(string reservationNumber) //�^�Ǥ@�ӫ��VreservationNumber�Ҧb�}�C��iterator
{
	for (int pos = 0; pos < reservations.size(); pos++)
	{
		if (reservations[pos].getReservationNumber() == reservationNumber) //�Y�Ӯ椺��reservationNumber�ŦX
		{
			return reservations.begin() + pos; //�Niterator���V�Ӯ�æ^��
		}
	}
}