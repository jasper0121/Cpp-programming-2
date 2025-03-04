#ifndef DEPOSIT_H
#define DEPOSIT_H

#include<iostream>
#include"account.h"
using namespace std;

class Deposit
{
public:
	void depositFunds(Account& account) //�s�ڥ\��
	{
		double cents; //��J�H"��"�����
		cout << "\nPlease enter a deposit amount in CENTS (or 0 to cancel): ";
		cin >> cents;
		if (cents /= 100) //��ڪ��B�n�����H100�A�Ycents == 0�h�����s��
		{
			cout << "\nPlease insert a deposit envelope containing $" << cents << " in the deposit slot.\n\n";
			account.accountDeposit(cents); //�s�ڪ��B�[�J�b��(��U�u��total_balance���ȷ|�W�[)
			cout << "Your envelope has been received.\n";
			cout << "NOTE: The money deposited will not be available until we\nverify the amount of any enclosed cash, and any enclosed checks clear.\n";
		}
	}
};

#endif