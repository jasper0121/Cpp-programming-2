#ifndef MAKERESERVATION_H
#define MAKERESERVATION_H

using namespace std;
#include"AvailTableDatabase.h" //�]�tAvailTable�BDate
#include"ReservationDatabase.h" //�]�tReservation�BAvailTable�BDate

class MakeReservation
{
public:
	void execute(AvailTableDatabase&, ReservationDatabase&); //����q��
private:
	AvailTable availTable; //�B�z�@�ѩҦ�����l
	Reservation reservation; //�B�z�@���q��
};

#endif