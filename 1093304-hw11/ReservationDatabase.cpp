#include<iostream>
#include"ReservationDatabase.h"

ReservationDatabase::ReservationDatabase() //constructor，讀檔
{
	ifstream inFile("Reservations.dat", ios::binary);

	if (!inFile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}

	for (Reservation data; inFile.read(reinterpret_cast<char*>(&data), sizeof(data));) //讀檔，轉成char後加入資料庫
	{
		reservationDatabase.push_back(data);
	}

	Date today; //今天的日期
	vector<Reservation>::iterator eraseItr = reservationDatabase.begin(); //eraseItr指向陣列的開頭(因erase的傳入值需要iterator)
	for (size_t pos = 0; pos < reservationDatabase.size(); )
	{
		if (beforeToday(today, reservationDatabase[pos])) //若現存在資料庫內的該筆訂單過期
		{
			eraseItr = reservationDatabase.erase(eraseItr); //刪除訂單(若需多次刪除，eraseItr須紀錄erase回傳的iterator，否則第二次會crash，窩不知道為什麼)
		}
		else //erase後當下指向的該格為erase前的下一格資料，故erase後不++
		{
			pos++, eraseItr++; //若當前該格不需erase，則往下一格檢查
		}
	}

	inFile.close();
}

Reservation ReservationDatabase::getReservation(const int& pos) const //回傳資料庫裡的某筆訂單
{
	return reservationDatabase[pos];
}

int ReservationDatabase::DatabaseSize() const //回傳資料庫size
{
	return reservationDatabase.size();
}

bool ReservationDatabase::beforeToday(const Date& today, const Reservation& reservation) const //算出是否過期
{
	if (today.getYear() == reservation.getDate().getYear()) //若年相同
	{
		if (today.getMonth() == reservation.getDate().getMonth()) //則繼續檢查，若月相同
		{
			return (today.getDay() >= reservation.getDate().getDay()); //則繼續檢查，若今天 >= 訂單日期，代表訂單已過期
		}
		else
		{
			return(today.getMonth() > reservation.getDate().getMonth()); //反之若今天的月較大，代表訂單已過期，回傳true，否則回傳false
		}
	}
	else
	{
		return (today.getYear() > reservation.getDate().getYear()); //反之若今天的年較大，代表訂單已過期，回傳true，否則回傳false
	}
}

void ReservationDatabase::writeInDatabase(const Reservation& reservation) //資料庫新增一筆訂單
{
	reservationDatabase.push_back(reservation);
	cout << "\n\nReservation Completed.\n\n";
}

void ReservationDatabase::eraseReservation(const int& pos) //刪除訂單
{
	vector<Reservation>::iterator eraseItr = reservationDatabase.begin(); //eraseItr作為erase的傳入值
	eraseItr._Ptr = &reservationDatabase[pos]; //iterator裡的Ptr指向欲刪除的位置
	reservationDatabase.erase(eraseItr);
}

ReservationDatabase::~ReservationDatabase() //destructor，寫檔
{
	ofstream outFile("Reservations.dat", ios::binary);

	for (size_t pos = 0; pos < reservationDatabase.size(); pos++) //寫檔，轉成const char後寫入dat檔
	{
		outFile.write(reinterpret_cast<const char*>(&reservationDatabase[pos]), sizeof(reservationDatabase[pos]));
	}

	outFile.close();
}