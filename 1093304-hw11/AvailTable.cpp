#include<iostream>
#include<string>
#include"AvailTable.h"

int AvailTable::chooseCustomers() const //��ܫȤH��
{
	int number;
	do
	{
		cout << "\nEnter the number of customers (1 - 7, 10 - 12): ";
	} while ((number = foolProof()) == -1); //���b

	return number; //�^�ǫȤH��
}

int AvailTable::getTableType(const int& customers) const //�N�ȤH���ഫ���ู
{
	const int tableType[13]{ 0,1,1,2,2,3,4,4,0,0,5,5,5 };
	return tableType[customers]; //�^�Ǯู
}

bool AvailTable::fullNumAvailTables(const int& timeCode, const int& tableType) const //�^�ǸӮɬq���ู�O�_�w��
{
	return (numAvailTables[timeCode][tableType] == 2);
}

bool AvailTable::fullTable(const int& tableType) const //�^�Ƿ�ѩҦ��ɬq���Ӻخู�O�_�w��
{
	return(numAvailTables[1][tableType] == 2 && numAvailTables[2][tableType] == 2 && numAvailTables[3][tableType] == 2);
}

void AvailTable::bookTable(const int& timeCode, const int& tableType) //�w�q�Ӯɬq��������l
{
	numAvailTables[timeCode][tableType]++;
}

void AvailTable::releaseTable(const int& timeCode, const int& tableType) //����Ӯɬq��������l
{
	numAvailTables[timeCode][tableType]--;
}

int AvailTable::foolProof() const //���b
{
	int number = 0;
	string choice;
	getline(cin, choice);
	for (size_t pos = 0; pos < choice.size(); pos++)
	{
		if (choice.size() > 2 || !('0' <= choice[pos] && choice[pos] <= '9') || choice[0] == '\0')
		{
			return -1; //�Y��J���r > 2  || �D�Ʀr || �S����J�Ӫ�����enter�A�h�^��-1
		}
		else
		{
			number += (choice[pos + 1] != '\0') ? (choice[pos] - '0') * 10 : (choice[pos] - '0'); //�Nchar�ഫ��int
		}
	}

	return ((1 <= number && number <= 7) || (10 <= number && number <= 12)) ? number : -1; //�Y��J���T�h�^�ǸӼơA�_�h�^��-1
}