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
	Search search; //�d��
	Withdraw withdraw; //����
	Deposit deposit; //�s��
	Account account[2]{}; //�b��
	account[0].accountInfo(12345, 54321, 1000.0, 1200.0); //�b���B�K�X�B�i�ξl�B�B�`�l�B
	account[1].accountInfo(98765, 56789, 200.0, 200.0);

	while (true) //ATM24�p�ɤ�����
	{
		cout << "Welcome!\n";

		size_t account_number = 0, account_pin = 0, pos = 0; //�b�B�K�B�Ӳձb�K�b�}�C�����Ҧb��m
		do
		{
			cout << "\nPlease enter your account number: ";
			cin >> account_number;
			cout << "\nEnter your PIN: ";
			cin >> account_pin;
		} while (checkAccountNumber(account_number, account_pin, account, pos) == false); //�Y�b�K���~�h���s��J

		while (true) //�b��J4���X���e���|�����b������
		{
			int choice;
			do
			{
				cout << "\nMain menu:\n1 - View my balance\n2 - Withdraw cash\n3 - Deposit funds\n4 - Exit\n\n";
				cout << "Enter a choice: ";
			} while ((choice = checkAnInteger(1, 4)) == -1); //�Y��J���b�d�򤺫h���s��J

			if (choice == 4) //���4�h���}������
			{
				cout << "\nExiting the system...\n\nThank you! Goodbye!\n\n";
				break;
			}

			switch (choice)
			{
			case 1:
				search.viewBalance(account[pos]); //�d�߾l�B
				break;
			case 2:
				withdraw.withdrawCash(account[pos]); //����
				break;
			case 3:
				deposit.depositFunds(account[pos]); //�s��
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
	if (begin <= choice && choice <= end) //�Y��J���Ʀb�d�򤺫h�^�ǸӼơA�_�h�^��-1
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
	for (int n = 0; n < 2; n++) //�ˬd�O�_���Ӳձb�K�A�Y���h�����ӱb�K���Ҧb��m
	{
		if (account[n].checkAccount(number, pin))
		{
			pos = n;
			return true;
		}
	}

	return false;
}