#include<iostream>
#include<iomanip>
#include"Reservation.h"

int Reservation::getCustomers() const //�^�ǫȤH��
{
	return numCustomers;
}

Date Reservation::getDate() const //�^�Ǥ��(�]�t�~�B��B��)
{
	return date;
}

int Reservation::getTimeCode() const //�^�Ǯɶ��N�X
{
	return time;
}

string Reservation::getPassword() const //�^�ǱK�X
{
	return password;
}

string Reservation::getReservationNumber() const //�^�ǭq��s��
{
	return reservationNumber;
}

string Reservation::getStringTime(const int& timeCode) const //�N�ɶ��N�X�ഫ���۹������ɶ�
{
	const string time[4]{ "","11:30" ,"14:30" , "17:30" };
	return time[timeCode];
}

void Reservation::inputNumCustomers(const int& customer) //�����ȤH��
{
	numCustomers = customer;
}

void Reservation::inputDate(const AvailTable& availTable) //�NavailTable�̪�����O���b�q��W
{
	date.inputDate(availTable.getYear(), availTable.getMonth(), availTable.getDay());
}

void Reservation::inputTimeCode(const int& timeCode) //�����ɶ��N�X
{
	time = timeCode;
}

void Reservation::inputPersonalInfo() //��J�Ӹ�(�t���b)
{
	do
	{
		cout << "\nEnter name: ";
		cin.getline(name, 8, '\n');
	} while (name[0] == '\0'); //�m�W

	do
	{
		cout << "\nEnter mobile number: ";
		cin.getline(mobileNumber, 12, '\n');
	} while (mobileNumber[0] == '\0'); //�q��

	do
	{
		cout << "\nEnter email address: ";
		cin.getline(email, 40, '\n');
	} while (email[0] == '\0'); //email

	do
	{
		cout << "\nEnter reservation password: ";
		cin.getline(password, 12, '\n');
	} while (password[0] == '\0'); //�K�X

	for (int n = 0; n < 8; n++) //�üƲ��ͭq��s��(�T�w8���)
	{
		reservationNumber[n] = (rand() % 10 + '0'); //�C����J�üƪ��Ӧ��(int��char)
	}
}

void Reservation::showReservation() const //��ܦ������q���T
{
	cout << "\nMobile No.      Name          Date     Time                         Email    No of Customers    Password    Reservation No.\n"
		<< setfill(' ') << setw(10) << mobileNumber << setw(10) << name
		<< setw(8) << date.getYear() << "/" << setfill('0') << setw(2) << date.getMonth() << "/" << setw(2) << date.getDay()
		<< setfill(' ') << setw(9) << getStringTime(time) << setw(30) << email << setw(19) << numCustomers << setw(12) << password
		<< setw(19) << reservationNumber;
}