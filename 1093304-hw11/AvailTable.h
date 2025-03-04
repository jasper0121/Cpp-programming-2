#ifndef AVAILTABLE_H
#define AVAILTABLE_H

#include"Date.h"
using namespace std;

class AvailTable :public Date //�~��Date
{
public:
	int chooseCustomers() const; //��ܫȤH��
	int getTableType(const int&) const; //�N�ȤH���ഫ���ู
	bool fullNumAvailTables(const int&, const int&) const; //�^�ǸӮɬq���ู�O�_�w��
	bool fullTable(const int&) const; //�^�Ƿ�ѩҦ��ɬq���Ӻخู�O�_�w��
	void bookTable(const int&, const int&); //�w�q�Ӯɬq��������l
	void releaseTable(const int&, const int&); //����Ӯɬq��������l
private:
	int numAvailTables[4][6]{}; //�����@�ѩҦ�����l
	int foolProof() const; //���b
};

#endif