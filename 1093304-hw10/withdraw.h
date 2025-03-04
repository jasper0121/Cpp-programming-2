#ifndef WITHDRAW_H
#define WITHDRAW_H

#include<iostream>
#include"account.h"

class Withdraw
{
public:
	void withdrawCash(Account& account) //提款功能
	{
		while (true) //在輸入6跳出或提款結束之前都會維持在此介面
		{
			int choice;
			do
			{
				cout << "\nWithdrawal options:\n1 - $20\n2 - $40\n3 - $60\n4 - $100\n5 - $200\n6 - Cancel transaction\n\n";
				cout << "Choose a withdrawal option (1-6): ";
			} while ((choice = checkAnInteger(1, 6)) == -1); //若輸入不在範圍內則重新輸入

			if (choice == 6) //若輸入6則取消提款
			{
				return;
			}

			size_t money = dollar(choice); //代表要提領的金額
			if (account.availableBalance() >= money) //若帳戶內的餘額充足
			{
				if ($20_bills >= money / 20) //若ATM裡的金額充足
				{
					$20_bills -= money / 20; //則提領所選擇的金額(每張紙鈔以$20為單位)
					account.accountWithdraw(money); //帳戶內的數減去所提領的金額
					cout << "\nPlease take your cash from the cash dispenser.\n";
					return; //提款結束
				}
				else
				{
					cout << "\nThe balance of the ATM is insufficient. Please select a smaller withdrawal amount.\n";
				}
			}
			else
			{
				cout << "\nThe withdrawal amount chosen is greater than your account balance. Please choose a smaller amount.\n";
			}
		}
	}

private:
	size_t $20_bills = 500; //ATM內$20的紙鈔數量

	int checkAnInteger(const int& begin, const int& end) //若輸入的數在範圍內則回傳該數，否則回傳-1
	{
		int choice;
		cin >> choice;
		if (begin <= choice && choice <= end)
		{
			return choice;
		}
		else
		{
			cout << "\nInput error. Please try again\n";
			return -1;
		}
	}

	int dollar(const int& choice) //回傳選擇提款的金額
	{
		return 20 * choice * (choice + 1) * ((choice - 3) * (choice - 4) + 6) / 24; //選擇與金額間的函數關係
	}
};

#endif