#include<iostream>
#include"ReservationDatabase.h"

ReservationDatabase::ReservationDatabase() //constructor�AŪ��
{
	ifstream inFile("Reservations.dat", ios::binary);

	if (!inFile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}

	for (Reservation data; inFile.read(reinterpret_cast<char*>(&data), sizeof(data));) //Ū�ɡA�নchar��[�J��Ʈw
	{
		reservationDatabase.push_back(data);
	}

	Date today; //���Ѫ����
	vector<Reservation>::iterator eraseItr = reservationDatabase.begin(); //eraseItr���V�}�C���}�Y(�]erase���ǤJ�Ȼݭniterator)
	for (size_t pos = 0; pos < reservationDatabase.size(); )
	{
		if (beforeToday(today, reservationDatabase[pos])) //�Y�{�s�b��Ʈw�����ӵ��q��L��
		{
			eraseItr = reservationDatabase.erase(eraseItr); //�R���q��(�Y�ݦh���R���AeraseItr������erase�^�Ǫ�iterator�A�_�h�ĤG���|crash�A�ۤ����D������)
		}
		else //erase���U���V���Ӯ欰erase�e���U�@���ơA�Gerase�ᤣ++
		{
			pos++, eraseItr++; //�Y��e�Ӯ椣��erase�A�h���U�@���ˬd
		}
	}

	inFile.close();
}

Reservation ReservationDatabase::getReservation(const int& pos) const //�^�Ǹ�Ʈw�̪��Y���q��
{
	return reservationDatabase[pos];
}

int ReservationDatabase::DatabaseSize() const //�^�Ǹ�Ʈwsize
{
	return reservationDatabase.size();
}

bool ReservationDatabase::beforeToday(const Date& today, const Reservation& reservation) const //��X�O�_�L��
{
	if (today.getYear() == reservation.getDate().getYear()) //�Y�~�ۦP
	{
		if (today.getMonth() == reservation.getDate().getMonth()) //�h�~���ˬd�A�Y��ۦP
		{
			return (today.getDay() >= reservation.getDate().getDay()); //�h�~���ˬd�A�Y���� >= �q�����A�N��q��w�L��
		}
		else
		{
			return(today.getMonth() > reservation.getDate().getMonth()); //�Ϥ��Y���Ѫ�����j�A�N��q��w�L���A�^��true�A�_�h�^��false
		}
	}
	else
	{
		return (today.getYear() > reservation.getDate().getYear()); //�Ϥ��Y���Ѫ��~���j�A�N��q��w�L���A�^��true�A�_�h�^��false
	}
}

void ReservationDatabase::writeInDatabase(const Reservation& reservation) //��Ʈw�s�W�@���q��
{
	reservationDatabase.push_back(reservation);
	cout << "\n\nReservation Completed.\n\n";
}

void ReservationDatabase::eraseReservation(const int& pos) //�R���q��
{
	vector<Reservation>::iterator eraseItr = reservationDatabase.begin(); //eraseItr�@��erase���ǤJ��
	eraseItr._Ptr = &reservationDatabase[pos]; //iterator�̪�Ptr���V���R������m
	reservationDatabase.erase(eraseItr);
}

ReservationDatabase::~ReservationDatabase() //destructor�A�g��
{
	ofstream outFile("Reservations.dat", ios::binary);

	for (size_t pos = 0; pos < reservationDatabase.size(); pos++) //�g�ɡA�নconst char��g�Jdat��
	{
		outFile.write(reinterpret_cast<const char*>(&reservationDatabase[pos]), sizeof(reservationDatabase[pos]));
	}

	outFile.close();
}