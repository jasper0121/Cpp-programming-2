#ifndef RESERVATIONINQUIRY_H
#define RESERVATIONINQUIRY_H

#include"AvailTableDatabase.h" //包含AvailTable、Date
#include"ReservationDatabase.h" //包含Reservation、AvailTable、Date
using namespace std;

class ReservationInquiry :public AvailTable //繼承AvailTable
{
public:
	void execute(AvailTableDatabase&, ReservationDatabase&) const; //執行查詢
private:
	void chooseCancel(AvailTableDatabase&, ReservationDatabase&, const int&) const; //選擇訂單刪除
};

#endif