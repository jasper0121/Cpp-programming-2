#ifndef RESERVATIONINQUIRY_H
#define RESERVATIONINQUIRY_H

#include"AvailTableDatabase.h" //�]�tAvailTable�BDate
#include"ReservationDatabase.h" //�]�tReservation�BAvailTable�BDate
using namespace std;

class ReservationInquiry :public AvailTable //�~��AvailTable
{
public:
	void execute(AvailTableDatabase&, ReservationDatabase&) const; //����d��
private:
	void chooseCancel(AvailTableDatabase&, ReservationDatabase&, const int&) const; //��ܭq��R��
};

#endif