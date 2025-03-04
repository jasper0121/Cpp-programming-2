#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace::std;

#include "ReservationDatabase.h" // ReservationDatabase class definition

extern Date computeCurrentDate();

// call loadReservations and removes outdated reservation informations
ReservationDatabase::ReservationDatabase() //constructor，讀檔並刪除舊訂單
{
	loadReservations();

	Date today = computeCurrentDate(); //今天的日期
	vector<Reservation>::iterator eraseItr = reservations.begin(); //eraseItr指向陣列的開頭
	for (size_t pos = 0; pos < reservations.size(); )
	{
		if (reservations[pos].getDate() <= today) //若現存在資料庫內的該筆訂單過期
		{
			reservations.erase(eraseItr); //刪除訂單
		}
		else //erase後當下指向的該格為erase前的下一格資料，故erase後不++
		{
			pos++, eraseItr++; //若當前該格不需erase，則往下一格檢查
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
bool ReservationDatabase::exist(string reservationNumber) //檢查reservations是否存在
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
bool ReservationDatabase::legal(string reservationNumber, string password) //檢查reservations和password是否存在
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
void ReservationDatabase::loadReservations() //讀檔
{
	ifstream inFile("Reservations.dat", ios::binary);

	if (!inFile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}

	for (Reservation data; inFile.read(reinterpret_cast<char*>(&data), sizeof(data)); reservations.push_back(data)); //轉成char後加入資料庫

	inFile.close();
}

// stores reservations into the file Reservations.dat
void ReservationDatabase::storeReservations() //寫檔
{
	ofstream outFile("Reservations.dat", ios::binary);

	for (size_t pos = 0; pos < reservations.size(); pos++) //轉成const char後寫入dat檔
	{
		outFile.write(reinterpret_cast<const char*>(&reservations[pos]), sizeof(reservations[pos]));
	}

	outFile.close();
}

// returns an iterator that points to the Reservation object containing specified reservationNumber
vector< Reservation >::iterator ReservationDatabase::getReservation(string reservationNumber) //回傳一個指向reservationNumber所在陣列的iterator
{
	for (int pos = 0; pos < reservations.size(); pos++)
	{
		if (reservations[pos].getReservationNumber() == reservationNumber) //若該格內的reservationNumber符合
		{
			return reservations.begin() + pos; //將iterator指向該格並回傳
		}
	}
}