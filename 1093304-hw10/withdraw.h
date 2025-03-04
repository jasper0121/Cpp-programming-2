#ifndef WITHDRAW_H
#define WITHDRAW_H

#include<iostream>
#include"account.h"

class Withdraw
{
public:
	void withdrawCash(Account& account) //���ڥ\��
	{
		while (true) //�b��J6���X�δ��ڵ������e���|�����b������
		{
			int choice;
			do
			{
				cout << "\nWithdrawal options:\n1 - $20\n2 - $40\n3 - $60\n4 - $100\n5 - $200\n6 - Cancel transaction\n\n";
				cout << "Choose a withdrawal option (1-6): ";
			} while ((choice = checkAnInteger(1, 6)) == -1); //�Y��J���b�d�򤺫h���s��J

			if (choice == 6) //�Y��J6�h��������
			{
				return;
			}

			size_t money = dollar(choice); //�N��n���⪺���B
			if (account.availableBalance() >= money) //�Y�b�᤺���l�B�R��
			{
				if ($20_bills >= money / 20) //�YATM�̪����B�R��
				{
					$20_bills -= money / 20; //�h����ҿ�ܪ����B(�C�i�ȶr�H$20�����)
					account.accountWithdraw(money); //�b�᤺���ƴ�h�Ҵ��⪺���B
					cout << "\nPlease take your cash from the cash dispenser.\n";
					return; //���ڵ���
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
	size_t $20_bills = 500; //ATM��$20���ȶr�ƶq

	int checkAnInteger(const int& begin, const int& end) //�Y��J���Ʀb�d�򤺫h�^�ǸӼơA�_�h�^��-1
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

	int dollar(const int& choice) //�^�ǿ�ܴ��ڪ����B
	{
		return 20 * choice * (choice + 1) * ((choice - 3) * (choice - 4) + 6) / 24; //��ܻP���B����������Y
	}
};

#endif