#ifndef SEARCH_H
#define SEARCH_H

#include<iostream>
#include"account.h"

class Search
{
public:
	void viewBalance(Account& account) //≈„•‹æl√B
	{
		cout << "\nBalance Information:";
		cout << "\n - Available balance: $" << account.availableBalance() << "\n - Total balance:     $" << account.totalBalance() << "\n";
	}
};

#endif