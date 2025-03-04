#include<iostream>
#include"account.h"
#include"search.h"
#include"withdraw.h"
#include"deposit.h"
using namespace std;

int checkAnInteger(const int& begin, const int& end);
bool checkAccountNumber(const size_t& number, const size_t& pin, Account account[], size_t& pos);

int main()
{
	Search search; //查詢
	Withdraw withdraw; //提款
	Deposit deposit; //存款
	Account account[2]{}; //帳戶
	account[0].accountInfo(12345, 54321, 1000.0, 1200.0); //帳號、密碼、可用餘額、總餘額
	account[1].accountInfo(98765, 56789, 200.0, 200.0);

	while (true) //ATM24小時不關機
	{
		cout << "Welcome!\n";

		size_t account_number = 0, account_pin = 0, pos = 0; //帳、密、該組帳密在陣列中的所在位置
		do
		{
			cout << "\nPlease enter your account number: ";
			cin >> account_number;
			cout << "\nEnter your PIN: ";
			cin >> account_pin;
		} while (checkAccountNumber(account_number, account_pin, account, pos) == false); //若帳密錯誤則重新輸入

		while (true) //在輸入4跳出之前都會維持在此介面
		{
			int choice;
			do
			{
				cout << "\nMain menu:\n1 - View my balance\n2 - Withdraw cash\n3 - Deposit funds\n4 - Exit\n\n";
				cout << "Enter a choice: ";
			} while ((choice = checkAnInteger(1, 4)) == -1); //若輸入不在範圍內則重新輸入

			if (choice == 4) //選擇4則離開此介面
			{
				cout << "\nExiting the system...\n\nThank you! Goodbye!\n\n";
				break;
			}

			switch (choice)
			{
			case 1:
				search.viewBalance(account[pos]); //查詢餘額
				break;
			case 2:
				withdraw.withdrawCash(account[pos]); //提款
				break;
			case 3:
				deposit.depositFunds(account[pos]); //存款
				break;
			}
		}
	}

	return 0;
}

int checkAnInteger(const int& begin, const int& end)
{
	int choice;
	cin >> choice;
	if (begin <= choice && choice <= end) //若輸入的數在範圍內則回傳該數，否則回傳-1
	{
		return choice;
	}
	else
	{
		cout << "\nInput error. Please try again\n";
		return -1;
	}
}

bool checkAccountNumber(const size_t& number, const size_t& pin, Account account[], size_t& pos)
{
	for (int n = 0; n < 2; n++) //檢查是否有該組帳密，若有則紀錄該帳密的所在位置
	{
		if (account[n].checkAccount(number, pin))
		{
			pos = n;
			return true;
		}
	}

	return false;
}