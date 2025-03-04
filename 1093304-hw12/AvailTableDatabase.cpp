#include <iostream>
#include <fstream>
using namespace::std;

#include "AvailTableDatabase.h"

// tableTypes[ i ] is the table type for i customers
const int tableTypes[13] = { 0, 1, 1, 2, 2, 3, 4, 4, 0, 0, 5, 5, 5 };

extern Date computeCurrentDate();

// calls loadAvailTables(), removes outdated available table informations and
// adds new available table informations
AvailTableDatabase::AvailTableDatabase() //constructor�AŪ�ɨç�s���
{
	loadAvailTables();

	Date today = computeCurrentDate(); //���Ѫ����
	//�Y��Ʈw��size != 0�B�q���Ƥw�L��(&&��2�䤣�i��աA�_�h�bsize == 0�U��Ū��availTables[0]�|crash)�A�h�R���L�������
	for (; availTables.size() != 0 && availTables[0].getDate() <= today; availTables.erase(availTables.begin()));

	AvailTable data; //�s�W�@����l�����
	for (int timeCode = 1; timeCode <= 3; timeCode++) //��l�ơA�C�Ӯɬq���C�خ�l�Ҧ�2��(totalNumTables)
	{
		for (int tableType = 1; tableType <= 5; tableType++)
		{
			data.setNumAvailTables(timeCode, tableType, totalNumTables);
		}
	}

	while (availTables.size() < 30) //�Y��Ʈw����l����� < 30
	{
		data.setDate(today + (availTables.size() + 1)); //�C���]�w�Ӯ��ƪ����(�̦���availTables.size() == 0�ɡA�Ӥ���q���Ѷ}�l)
		availTables.push_back(data); //�s�W�@����Ѯ�l�����
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
bool AvailTableDatabase::availableTables(int numCustomers, Date date) //�^�Ƿ�ѩҦ��ɬq���Ӻخู�O�_�w��
{
	Date today = computeCurrentDate(); //���Ѫ����
	for (int timeCode = 1; timeCode <= 3; timeCode++) //(date - today) - 1 == ����t - 1 == date�b�}�C�����Ҧb��m
	{
		if (availTables[(date - today) - 1].getNumAvailTables(timeCode, tableTypes[numCustomers]) > 0) //0�N��Ҥw�Q�w�q
		{
			return true; //�Y������ɬq�����w�ู�٦��Ѿl�A�h�^��true
		}
	}

	return false; //�U�ɬq�����w�ู�ҵL�Ѿl�h�^��false
}

// returns true if there are available tables on date and timeCode for corresponding table type
bool AvailTableDatabase::availableTables(int numCustomers, Date date, int timeCode) //�^�ǸӮɬq���ู�O�_�w��(today == computeCurrentDate())
{
	return (availTables[(date - computeCurrentDate()) - 1].getNumAvailTables(timeCode, tableTypes[numCustomers]) > 0);
}

void AvailTableDatabase::loadAvailTables() //Ū��
{
	ifstream inFile("AvailTables.dat", ios::binary);

	if (!inFile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}

	for (AvailTable data; inFile.read(reinterpret_cast<char*>(&data), sizeof(data)); availTables.push_back(data)); //�নchar��[�J��Ʈw

	inFile.close();
}

void AvailTableDatabase::storeAvailTables() //�g��
{
	ofstream outFile("AvailTables.dat", ios::binary);

	for (size_t pos = 0; pos < availTables.size(); pos++) //�নconst char��g�Jdat��
	{
		outFile.write(reinterpret_cast<const char*>(&availTables[pos]), sizeof(availTables[pos]));
	}

	outFile.close();
}

// returns an iterator that points to the AvailTable object containing specified date
vector< AvailTable >::iterator AvailTableDatabase::getAvailTable(Date date) //�^�Ǥ@�ӫ��Vdate�Ҧb�}�C��iterator
{
	return availTables.begin() + (date - computeCurrentDate() - 1); //today == computeCurrentDate()
}