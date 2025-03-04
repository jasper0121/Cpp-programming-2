#include"MakeReservation.h"

void MakeReservation::execute(AvailTableDatabase& availTableDatabase, ReservationDatabase& reservationDatabase)
{
	int customer = availTable.chooseCustomers(); //��ܫȤH��
	reservation.inputNumCustomers(customer); //�N�ȤH�ưO���b�q��W
	int tableType = availTable.getTableType(customer); //�N�ȤH���ഫ���ู
	int dateCode; //����N�X
	reservation.inputDate(availTableDatabase.chooseDate(dateCode, tableType)); //��ܤ���ñN��O���b�q��W
	int timeCode = availTableDatabase.chooseTime(dateCode, tableType); //��ܮɶ�
	reservation.inputTimeCode(timeCode); //�N�ɶ��N�X�O���b�q��W
	reservation.inputPersonalInfo(); //��J�Ӹ�(�m�W�B�q�ܡBemail�B�K�X�B�üƲ��ͭq�渹�X)
	reservation.showReservation(); //��ܦ������q���T
	availTableDatabase.updateDatabase(dateCode, timeCode, customer); //��s�Ӥ骺��p
	reservationDatabase.writeInDatabase(reservation); //��Ʈw�s�W�@���q��
}