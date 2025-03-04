#ifndef ACCOUNT_H
#define ACCOUNT_H

#include<iostream>
using namespace std;

class Account
{
public:
	void accountInfo(const size_t& number, const size_t& pin, const double& available, const double& total) //�x�s�ӱb�᪺�b�K�M�l�B
	{
		account_number = number;
		account_pin = pin;
		available_balance = available;
		total_balance = total;
	}

	bool checkAccount(const size_t& number, const size_t& pin) //�ˬd�b�K�O�_�ŦX
	{
		return (account_number == number && account_pin == pin);
	}

	double availableBalance() //�^�ǥi�ξl�B
	{
		return available_balance;
	}

	double totalBalance() //�^���`�l�B
	{
		return total_balance;
	}

	void accountWithdraw(const size_t& dollar) //�b�ᴣ��
	{
		available_balance -= dollar;
		total_balance -= dollar;
	}

	void accountDeposit(const double& dollar) //�b��s��
	{
		total_balance += dollar;
	}

private:
	size_t account_number;
	size_t account_pin;
	double available_balance;
	double total_balance;
};

#endif