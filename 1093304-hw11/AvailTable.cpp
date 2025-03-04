#include<iostream>
#include<string>
#include"AvailTable.h"

int AvailTable::chooseCustomers() const //選擇客人數
{
	int number;
	do
	{
		cout << "\nEnter the number of customers (1 - 7, 10 - 12): ";
	} while ((number = foolProof()) == -1); //防呆

	return number; //回傳客人數
}

int AvailTable::getTableType(const int& customers) const //將客人數轉換成桌號
{
	const int tableType[13]{ 0,1,1,2,2,3,4,4,0,0,5,5,5 };
	return tableType[customers]; //回傳桌號
}

bool AvailTable::fullNumAvailTables(const int& timeCode, const int& tableType) const //回傳該時段的桌號是否已滿
{
	return (numAvailTables[timeCode][tableType] == 2);
}

bool AvailTable::fullTable(const int& tableType) const //回傳當天所有時段的該種桌號是否已滿
{
	return(numAvailTables[1][tableType] == 2 && numAvailTables[2][tableType] == 2 && numAvailTables[3][tableType] == 2);
}

void AvailTable::bookTable(const int& timeCode, const int& tableType) //預訂該時段對應的桌子
{
	numAvailTables[timeCode][tableType]++;
}

void AvailTable::releaseTable(const int& timeCode, const int& tableType) //釋放該時段對應的桌子
{
	numAvailTables[timeCode][tableType]--;
}

int AvailTable::foolProof() const //防呆
{
	int number = 0;
	string choice;
	getline(cin, choice);
	for (size_t pos = 0; pos < choice.size(); pos++)
	{
		if (choice.size() > 2 || !('0' <= choice[pos] && choice[pos] <= '9') || choice[0] == '\0')
		{
			return -1; //若輸入的字 > 2  || 非數字 || 沒有輸入而直接按enter，則回傳-1
		}
		else
		{
			number += (choice[pos + 1] != '\0') ? (choice[pos] - '0') * 10 : (choice[pos] - '0'); //將char轉換成int
		}
	}

	return ((1 <= number && number <= 7) || (10 <= number && number <= 12)) ? number : -1; //若輸入正確則回傳該數，否則回傳-1
}