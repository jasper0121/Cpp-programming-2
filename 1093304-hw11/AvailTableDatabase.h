#ifndef AVAILTABLEDATABASE_H
#define AVAILTABLEDATABASE_H

#include<vector>
#include"AvailTable.h" //包含Date
using namespace std;

class AvailTableDatabase
{
public:
	AvailTableDatabase(); //constructor，讀檔
	AvailTable chooseDate(int&, const int&) const; //選擇日期
	int chooseTime(const int&, const int&) const; //選擇時間
	bool beforeToday(const Date&, const AvailTable&) const; //算出是否過期
	void updateDatabase(const int&, const int&, const int&); //更新該日的桌況
	void cancelBook(const Date&, const int&, const int&); //取消訂位
	~AvailTableDatabase(); //destructor，寫檔
private:
	vector<AvailTable>availTableDatabase; //含所有30天桌子的資料庫
	int foolProof(const int&, const int&) const; //防呆
};

#endif