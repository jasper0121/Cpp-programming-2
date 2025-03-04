#ifndef AVAILTABLE_H
#define AVAILTABLE_H

#include"Date.h"
using namespace std;

class AvailTable :public Date //繼承Date
{
public:
	int chooseCustomers() const; //選擇客人數
	int getTableType(const int&) const; //將客人數轉換成桌號
	bool fullNumAvailTables(const int&, const int&) const; //回傳該時段的桌號是否已滿
	bool fullTable(const int&) const; //回傳當天所有時段的該種桌號是否已滿
	void bookTable(const int&, const int&); //預訂該時段對應的桌子
	void releaseTable(const int&, const int&); //釋放該時段對應的桌子
private:
	int numAvailTables[4][6]{}; //紀錄一天所有的桌子
	int foolProof() const; //防呆
};

#endif