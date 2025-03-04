#ifndef RESERVATION_H
#define RESERVATION_H

#include"AvailTable.h" //�]�tDate
using namespace std;

class Reservation
{
public:
	int getCustomers() const; //�^�ǫȤH��
	Date getDate() const; //�^�Ǥ��(�]�t�~�B��B��)
	int getTimeCode() const; //�^�Ǯɶ��N�X
	string getPassword() const; //�^�ǱK�X
	string getReservationNumber() const; //�^�ǭq��s��
	string getStringTime(const int&) const; //�N�ɶ��N�X�ഫ���۹������ɶ�
	void inputNumCustomers(const int&); //�����ȤH��
	void inputDate(const AvailTable&); //�NavailTable�̪�����O���b�q��W
	void inputTimeCode(const int&); //�����ɶ��N�X
	void inputPersonalInfo(); //��J�Ӹ�(�t���b)
	void showReservation() const; //��ܦ������q���T
private:
	int numCustomers = 0;
	Date date = Date();
	int time = 0;
	char name[8] = "";
	char mobileNumber[12] = "";
	char email[40] = "";
	char password[12] = "";
	char reservationNumber[12] = "";
};

#endif