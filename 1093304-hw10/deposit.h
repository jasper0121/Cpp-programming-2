#ifndef DEPOSIT_H
#define DEPOSIT_H

#include<iostream>
#include"account.h"
using namespace std;

class Deposit
{
public:
	void depositFunds(Account& account) //存款功能
	{
		double cents; //輸入以"分"為單位
		cout << "\nPlease enter a deposit amount in CENTS (or 0 to cancel): ";
		cin >> cents;
		if (cents /= 100) //實際金額要先除以100，若cents == 0則取消存款
		{
			cout << "\nPlease insert a deposit envelope containing $" << cents << " in the deposit slot.\n\n";
			account.accountDeposit(cents); //存款金額加入帳號(當下只有total_balance的值會增加)
			cout << "Your envelope has been received.\n";
			cout << "NOTE: The money deposited will not be available until we\nverify the amount of any enclosed cash, and any enclosed checks clear.\n";
		}
	}
};

#endif