#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include"AvailTableDatabase.h"

AvailTableDatabase::AvailTableDatabase() //constructor�AŪ��
{
	ifstream inFile("AvailTables.dat", ios::binary);

	if (!inFile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}

	for (AvailTable data; inFile.read(reinterpret_cast<char*>(&data), sizeof(data));) //Ū�ɡA�নchar��[�J��Ʈw
	{
		availTableDatabase.push_back(data);
	}

	//���إߤ��Ѫ�����A�Y��Ʈw��size != 0�B�q���Ƥw�L��(&&��2�䤣�i��աA�_�h�bsize == 0�U��Ū��availTableDatabase[0]�|crash)
	for (Date today; availTableDatabase.size() != 0 && beforeToday(today, availTableDatabase[0]);)
	{
		availTableDatabase.erase(availTableDatabase.begin()); //�C���N�L������ƧR��
	}

	//�Y��e��Ʈwsize == 0�A�hWithin_30_days�̪������l�ơA�_�h�q��Ʈw�̫�@�檺����}�l
	AvailTable Within_30_days = (availTableDatabase.size() == 0) ? AvailTable() : availTableDatabase[availTableDatabase.size() - 1];
	while (Within_30_days.dayAddition(), availTableDatabase.size() < 30) //�C�����N��e����� + 1�A�bsize < 30���e(�~��dayAddition)
	{
		availTableDatabase.push_back(Within_30_days); //�s�W�@����Ѯ�l�����
	}

	inFile.close();
}

AvailTable AvailTableDatabase::chooseDate(int& dateCode, const int& tableType) const //��ܤ��
{
	cout << "\nChoose a date";
	for (int pos = 0, counter = 0; pos < 30; pos++)
	{
		if (availTableDatabase[pos].fullTable(tableType)) //�Y�ӤѦU�ɬq�ҿ諸�ู�Ҥw�Q�w�q
		{
			continue; //�h�L�k�A��ܸӤѪ��ู�A�G���L�X�Ӥ��
		}

		if (counter % 4 == 0) //�C���4�Ӥ���h����
		{
			counter = 0;
			cout << endl;
		}

		cout << setfill(' ') << setw(2) << pos + 1 << ". " << availTableDatabase[pos].getYear() << "/"
			<< setfill('0') << setw(2) << availTableDatabase[pos].getMonth() << "/"
			<< setw(2) << availTableDatabase[pos].getDay() << "   "; //�L�X�~���(�~��getYear�BgetMonth�BgetDay)

		counter++; //������e�Ӧ�w�L�X�X�Ӥ��
	}

	do //���b�A�Y��J���~�ο�ܤw�����ู�h���s��J(availTableDatabase�̨C��}�C��m == dateCode - 1)
	{
		cout << "\n?";
	} while ((dateCode = foolProof(1, 30)) == -1 || availTableDatabase[dateCode - 1].fullTable(tableType));

	return availTableDatabase[dateCode - 1]; //�^�ǸӤѪ��Ҧ���l
}

int AvailTableDatabase::chooseTime(const int& choice_dateCode, const int& tableType) const //��ܮɶ�
{
	const string time[4]{ "", "11:30","14:30" ,"17:30" };
	cout << "\nChoose a time:";
	for (int n = 1; n <= 3; n++) //��ɶ�
	{
		if (availTableDatabase[choice_dateCode - 1].fullNumAvailTables(n, tableType)) //�Y�Ӯɬq�Ӯู�w�q�w���A�h�Ӯɬq�����
		{
			continue;
		}

		cout << "\n" << n << ". " << time[n];
	}

	int choice;
	do //���b�A�Y��J���~�ο�ܤw�����ู�h���s��J
	{
		cout << "\n? ";
	} while ((choice = foolProof(1, 3)) == -1 || availTableDatabase[choice_dateCode - 1].fullNumAvailTables(choice, tableType));

	return choice;
}

bool AvailTableDatabase::beforeToday(const Date& today, const AvailTable& availTable) const //��X�O�_�L��
{
	if (today.getYear() == availTable.getYear()) //�Y�~�ۦP(availTable�~��getYear�BgetMonth�BgetDay)
	{
		if (today.getMonth() == availTable.getMonth()) //�h�~���ˬd�A�Y��ۦP
		{
			return (today.getDay() >= availTable.getDay()); //�h�~���ˬd�A�Y���� >= �q�����A�N��q��w�L��
		}
		else
		{
			return(today.getMonth() > availTable.getMonth()); //�Ϥ��Y���Ѫ�����j�A�N��q��w�L���A�^��true�A�_�h�^��false
		}
	}
	else
	{
		return (today.getYear() > availTable.getYear()); //�Ϥ��Y���Ѫ��~���j�A�N��q��w�L���A�^��true�A�_�h�^��false
	}
}

void AvailTableDatabase::updateDatabase(const int& dateCode, const int& timeCode, const int& customer) //��s�Ӥ骺�q�챡�p
{
	availTableDatabase[dateCode - 1].bookTable(timeCode, availTableDatabase[dateCode - 1].getTableType(customer));
}

void AvailTableDatabase::cancelBook(const Date& date, const int& timeCode, const int& tableType) //�����q��
{
	for (size_t pos = 0; pos < availTableDatabase.size(); pos++)
	{
		if (availTableDatabase[pos].getYear() == date.getYear() && availTableDatabase[pos].getMonth() == date.getMonth()
			&& availTableDatabase[pos].getDay() == date.getDay()) //�������q��������(availTableDatabase[pos]�~��getYear�BgetMonth�BgetDay)
		{
			availTableDatabase[pos].releaseTable(timeCode, tableType); //���X��l
		}
	}
}

AvailTableDatabase::~AvailTableDatabase() //destructor�A�g��
{
	ofstream outFile("AvailTables.dat", ios::binary);

	for (size_t pos = 0; pos < availTableDatabase.size(); pos++) //�g�ɡA�নconst char��g�Jdat��
	{
		outFile.write(reinterpret_cast<const char*>(&availTableDatabase[pos]), sizeof(availTableDatabase[pos]));
	}

	outFile.close();
}

int AvailTableDatabase::foolProof(const int& begin, const int& end) const //���b
{
	int number = 0;
	string choice;
	getline(cin, choice);
	for (size_t pos = 0; pos < choice.size(); pos++)
	{
		if (choice.size() > 2 || !('0' <= choice[pos] && choice[pos] <= '9') || choice[0] == '\0')
		{
			return -1; //�Y��J���r > 2  || �D�Ʀr || �S����J�Ӫ�����enter�A�h�^��-1
		}
		else
		{
			number += (choice[pos + 1] != '\0') ? (choice[pos] - '0') * 10 : (choice[pos] - '0'); //�Nchar�ഫ��int
		}
	}

	return (begin <= number && number <= end) ? number : -1; //�Y��J�b�d�򤺫h�^�ǸӼơA�_�h�^��-1
}