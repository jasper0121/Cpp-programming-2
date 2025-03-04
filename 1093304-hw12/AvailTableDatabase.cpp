#include <iostream>
#include <fstream>
using namespace::std;

#include "AvailTableDatabase.h"

// tableTypes[ i ] is the table type for i customers
const int tableTypes[13] = { 0, 1, 1, 2, 2, 3, 4, 4, 0, 0, 5, 5, 5 };

extern Date computeCurrentDate();

// calls loadAvailTables(), removes outdated available table informations and
// adds new available table informations
AvailTableDatabase::AvailTableDatabase() //constructor，讀檔並更新資料
{
	loadAvailTables();

	Date today = computeCurrentDate(); //今天的日期
	//若資料庫的size != 0且訂桌資料已過期(&&的2邊不可對調，否則在size == 0下先讀取availTables[0]會crash)，則刪除過期的資料
	for (; availTables.size() != 0 && availTables[0].getDate() <= today; availTables.erase(availTables.begin()));

	AvailTable data; //新增一筆桌子的資料
	for (int timeCode = 1; timeCode <= 3; timeCode++) //初始化，每個時段的每種桌子皆有2桌(totalNumTables)
	{
		for (int tableType = 1; tableType <= 5; tableType++)
		{
			data.setNumAvailTables(timeCode, tableType, totalNumTables);
		}
	}

	while (availTables.size() < 30) //若資料庫內桌子的資料 < 30
	{
		data.setDate(today + (availTables.size() + 1)); //每次設定該桌資料的日期(最早為availTables.size() == 0時，該日期從明天開始)
		availTables.push_back(data); //新增一筆當天桌子的資料
	}
}

// call storeAvailTables
AvailTableDatabase::~AvailTableDatabase()
{
	storeAvailTables();
}

// increases the number of available tables by one on date and timeCode for corresponding table type
void AvailTableDatabase::increaseAvailTables(int numCustomers, Date date, int timeCode)
{
	int tableType = tableTypes[numCustomers];
	vector< AvailTable >::iterator it = getAvailTable(date);
	it->increaseAvailTables(timeCode, tableType);
}

// decreases the number of available tables by one on date and timeCode for corresponding table type
void AvailTableDatabase::decreaseAvailTables(int numCustomers, Date date, int timeCode)
{
	int tableType = tableTypes[numCustomers];
	vector< AvailTable >::iterator it = getAvailTable(date);
	it->decreaseAvailTables(timeCode, tableType);
}

// returns true if there are available tables on date for corresponding table type
bool AvailTableDatabase::availableTables(int numCustomers, Date date) //回傳當天所有時段的該種桌號是否已滿
{
	Date today = computeCurrentDate(); //今天的日期
	for (int timeCode = 1; timeCode <= 3; timeCode++) //(date - today) - 1 == 日期差 - 1 == date在陣列中的所在位置
	{
		if (availTables[(date - today) - 1].getNumAvailTables(timeCode, tableTypes[numCustomers]) > 0) //0代表皆已被預訂
		{
			return true; //若有任何時段的指定桌號還有剩餘，則回傳true
		}
	}

	return false; //各時段的指定桌號皆無剩餘則回傳false
}

// returns true if there are available tables on date and timeCode for corresponding table type
bool AvailTableDatabase::availableTables(int numCustomers, Date date, int timeCode) //回傳該時段的桌號是否已滿(today == computeCurrentDate())
{
	return (availTables[(date - computeCurrentDate()) - 1].getNumAvailTables(timeCode, tableTypes[numCustomers]) > 0);
}

void AvailTableDatabase::loadAvailTables() //讀檔
{
	ifstream inFile("AvailTables.dat", ios::binary);

	if (!inFile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}

	for (AvailTable data; inFile.read(reinterpret_cast<char*>(&data), sizeof(data)); availTables.push_back(data)); //轉成char後加入資料庫

	inFile.close();
}

void AvailTableDatabase::storeAvailTables() //寫檔
{
	ofstream outFile("AvailTables.dat", ios::binary);

	for (size_t pos = 0; pos < availTables.size(); pos++) //轉成const char後寫入dat檔
	{
		outFile.write(reinterpret_cast<const char*>(&availTables[pos]), sizeof(availTables[pos]));
	}

	outFile.close();
}

// returns an iterator that points to the AvailTable object containing specified date
vector< AvailTable >::iterator AvailTableDatabase::getAvailTable(Date date) //回傳一個指向date所在陣列的iterator
{
	return availTables.begin() + (date - computeCurrentDate() - 1); //today == computeCurrentDate()
}