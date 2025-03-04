#ifndef ACCOUNT_H
#define ACCOUNT_H

#include<iostream>
using namespace std;

class Account
{
public:
	void accountInfo(const size_t& number, const size_t& pin, const double& available, const double& total) //儲存該帳戶的帳密和餘額
	{
		account_number = number;
		account_pin = pin;
		available_balance = available;
		total_balance = total;
	}

	bool checkAccount(const size_t& number, const size_t& pin) //檢查帳密是否符合
	{
		return (account_number == number && account_pin == pin);
	}

	double availableBalance() //回傳可用餘額
	{
		return available_balance;
	}

	double totalBalance() //回傳總餘額
	{
		return total_balance;
	}

	void accountWithdraw(const size_t& dollar) //帳戶提款
	{
		available_balance -= dollar;
		total_balance -= dollar;
	}

	void accountDeposit(const double& dollar) //帳戶存款
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