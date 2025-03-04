#ifndef RESERVATIONDATABASE_H
#define RESERVATIONDATABASE_H

#include<fstream>
#include<vector>
#include"Reservation.h" //包含AvailTable、Date
using namespace std;

class ReservationDatabase
{
public:
	ReservationDatabase(); //constructor，讀檔
	Reservation getReservation(const int&) const; //回傳資料庫裡的某筆訂單
	int DatabaseSize() const; //回傳資料庫size
	bool beforeToday(const Date&, const Reservation&) const; //算出是否過期
	void writeInDatabase(const Reservation&); //資料庫新增一筆訂單
	void eraseReservation(const int&); //刪除訂單
	~ReservationDatabase(); //destructor，寫檔
private:
	vector<Reservation>reservationDatabase; //含所有訂單的資料庫
};

#endif