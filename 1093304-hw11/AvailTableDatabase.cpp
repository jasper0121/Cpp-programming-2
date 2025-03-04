#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include"AvailTableDatabase.h"

AvailTableDatabase::AvailTableDatabase() //constructor，讀檔
{
	ifstream inFile("AvailTables.dat", ios::binary);

	if (!inFile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}

	for (AvailTable data; inFile.read(reinterpret_cast<char*>(&data), sizeof(data));) //讀檔，轉成char後加入資料庫
	{
		availTableDatabase.push_back(data);
	}

	//先建立今天的日期，若資料庫的size != 0且訂桌資料已過期(&&的2邊不可對調，否則在size == 0下先讀取availTableDatabase[0]會crash)
	for (Date today; availTableDatabase.size() != 0 && beforeToday(today, availTableDatabase[0]);)
	{
		availTableDatabase.erase(availTableDatabase.begin()); //每次將過期的資料刪除
	}

	//若當前資料庫size == 0，則Within_30_days裡的日期初始化，否則從資料庫最後一格的日期開始
	AvailTable Within_30_days = (availTableDatabase.size() == 0) ? AvailTable() : availTableDatabase[availTableDatabase.size() - 1];
	while (Within_30_days.dayAddition(), availTableDatabase.size() < 30) //每次先將當前的日期 + 1，在size < 30之前(繼承dayAddition)
	{
		availTableDatabase.push_back(Within_30_days); //新增一筆當天桌子的資料
	}

	inFile.close();
}

AvailTable AvailTableDatabase::chooseDate(int& dateCode, const int& tableType) const //選擇日期
{
	cout << "\nChoose a date";
	for (int pos = 0, counter = 0; pos < 30; pos++)
	{
		if (availTableDatabase[pos].fullTable(tableType)) //若該天各時段所選的桌號皆已被預訂
		{
			continue; //則無法再選擇該天的桌號，故不印出該日期
		}

		if (counter % 4 == 0) //每顯示4個日期則換行
		{
			counter = 0;
			cout << endl;
		}

		cout << setfill(' ') << setw(2) << pos + 1 << ". " << availTableDatabase[pos].getYear() << "/"
			<< setfill('0') << setw(2) << availTableDatabase[pos].getMonth() << "/"
			<< setw(2) << availTableDatabase[pos].getDay() << "   "; //印出年月日(繼承getYear、getMonth、getDay)

		counter++; //紀錄當前該行已印出幾個日期
	}

	do //防呆，若輸入錯誤或選擇已滿的桌號則重新輸入(availTableDatabase裡每格陣列位置 == dateCode - 1)
	{
		cout << "\n?";
	} while ((dateCode = foolProof(1, 30)) == -1 || availTableDatabase[dateCode - 1].fullTable(tableType));

	return availTableDatabase[dateCode - 1]; //回傳該天的所有桌子
}

int AvailTableDatabase::chooseTime(const int& choice_dateCode, const int& tableType) const //選擇時間
{
	const string time[4]{ "", "11:30","14:30" ,"17:30" };
	cout << "\nChoose a time:";
	for (int n = 1; n <= 3; n++) //選時間
	{
		if (availTableDatabase[choice_dateCode - 1].fullNumAvailTables(n, tableType)) //若該時段該桌號預訂已滿，則該時段不顯示
		{
			continue;
		}

		cout << "\n" << n << ". " << time[n];
	}

	int choice;
	do //防呆，若輸入錯誤或選擇已滿的桌號則重新輸入
	{
		cout << "\n? ";
	} while ((choice = foolProof(1, 3)) == -1 || availTableDatabase[choice_dateCode - 1].fullNumAvailTables(choice, tableType));

	return choice;
}

bool AvailTableDatabase::beforeToday(const Date& today, const AvailTable& availTable) const //算出是否過期
{
	if (today.getYear() == availTable.getYear()) //若年相同(availTable繼承getYear、getMonth、getDay)
	{
		if (today.getMonth() == availTable.getMonth()) //則繼續檢查，若月相同
		{
			return (today.getDay() >= availTable.getDay()); //則繼續檢查，若今天 >= 訂位日期，代表訂位已過期
		}
		else
		{
			return(today.getMonth() > availTable.getMonth()); //反之若今天的月較大，代表訂位已過期，回傳true，否則回傳false
		}
	}
	else
	{
		return (today.getYear() > availTable.getYear()); //反之若今天的年較大，代表訂位已過期，回傳true，否則回傳false
	}
}

void AvailTableDatabase::updateDatabase(const int& dateCode, const int& timeCode, const int& customer) //更新該日的訂位情況
{
	availTableDatabase[dateCode - 1].bookTable(timeCode, availTableDatabase[dateCode - 1].getTableType(customer));
}

void AvailTableDatabase::cancelBook(const Date& date, const int& timeCode, const int& tableType) //取消訂位
{
	for (size_t pos = 0; pos < availTableDatabase.size(); pos++)
	{
		if (availTableDatabase[pos].getYear() == date.getYear() && availTableDatabase[pos].getMonth() == date.getMonth()
			&& availTableDatabase[pos].getDay() == date.getDay()) //找到取消訂位對應日期(availTableDatabase[pos]繼承getYear、getMonth、getDay)
		{
			availTableDatabase[pos].releaseTable(timeCode, tableType); //釋出桌子
		}
	}
}

AvailTableDatabase::~AvailTableDatabase() //destructor，寫檔
{
	ofstream outFile("AvailTables.dat", ios::binary);

	for (size_t pos = 0; pos < availTableDatabase.size(); pos++) //寫檔，轉成const char後寫入dat檔
	{
		outFile.write(reinterpret_cast<const char*>(&availTableDatabase[pos]), sizeof(availTableDatabase[pos]));
	}

	outFile.close();
}

int AvailTableDatabase::foolProof(const int& begin, const int& end) const //防呆
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

	return (begin <= number && number <= end) ? number : -1; //若輸入在範圍內則回傳該數，否則回傳-1
}