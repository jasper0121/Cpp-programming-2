#ifndef SEARCH_H
#define SEARCH_H

#include<iostream>
#include"account.h"

class Search
{
public:
	void viewBalance(Account& account) //��ܾl�B
	{
		cout << "\nBalance Information:";
		cout << "\n - Available balance: $" << account.availableBalance() << "\n - Total balance:     $" << account.totalBalance() << "\n";
	}
};

#endif