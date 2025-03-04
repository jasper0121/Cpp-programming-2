#ifndef MAKERESERVATION_H
#define MAKERESERVATION_H

using namespace std;
#include"AvailTableDatabase.h" //包含AvailTable、Date
#include"ReservationDatabase.h" //包含Reservation、AvailTable、Date

class MakeReservation
{
public:
	void execute(AvailTableDatabase&, ReservationDatabase&); //執行訂桌
private:
	AvailTable availTable; //處理一天所有的桌子
	Reservation reservation; //處理一筆訂單
};

#endif