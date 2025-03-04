#ifndef RESERVATIONDATABASE_H
#define RESERVATIONDATABASE_H

#include<fstream>
#include<vector>
#include"Reservation.h" //�]�tAvailTable�BDate
using namespace std;

class ReservationDatabase
{
public:
	ReservationDatabase(); //constructor�AŪ��
	Reservation getReservation(const int&) const; //�^�Ǹ�Ʈw�̪��Y���q��
	int DatabaseSize() const; //�^�Ǹ�Ʈwsize
	bool beforeToday(const Date&, const Reservation&) const; //��X�O�_�L��
	void writeInDatabase(const Reservation&); //��Ʈw�s�W�@���q��
	void eraseReservation(const int&); //�R���q��
	~ReservationDatabase(); //destructor�A�g��
private:
	vector<Reservation>reservationDatabase; //�t�Ҧ��q�檺��Ʈw
};

#endif