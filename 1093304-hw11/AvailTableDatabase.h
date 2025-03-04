#ifndef AVAILTABLEDATABASE_H
#define AVAILTABLEDATABASE_H

#include<vector>
#include"AvailTable.h" //�]�tDate
using namespace std;

class AvailTableDatabase
{
public:
	AvailTableDatabase(); //constructor�AŪ��
	AvailTable chooseDate(int&, const int&) const; //��ܤ��
	int chooseTime(const int&, const int&) const; //��ܮɶ�
	bool beforeToday(const Date&, const AvailTable&) const; //��X�O�_�L��
	void updateDatabase(const int&, const int&, const int&); //��s�Ӥ骺��p
	void cancelBook(const Date&, const int&, const int&); //�����q��
	~AvailTableDatabase(); //destructor�A�g��
private:
	vector<AvailTable>availTableDatabase; //�t�Ҧ�30�Ѯ�l����Ʈw
	int foolProof(const int&, const int&) const; //���b
};

#endif