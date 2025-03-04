#include"MakeReservation.h"

void MakeReservation::execute(AvailTableDatabase& availTableDatabase, ReservationDatabase& reservationDatabase)
{
	int customer = availTable.chooseCustomers(); //選擇客人數
	reservation.inputNumCustomers(customer); //將客人數記錄在訂單上
	int tableType = availTable.getTableType(customer); //將客人數轉換成桌號
	int dateCode; //日期代碼
	reservation.inputDate(availTableDatabase.chooseDate(dateCode, tableType)); //選擇日期並將其記錄在訂單上
	int timeCode = availTableDatabase.chooseTime(dateCode, tableType); //選擇時間
	reservation.inputTimeCode(timeCode); //將時間代碼記錄在訂單上
	reservation.inputPersonalInfo(); //輸入個資(姓名、電話、email、密碼、亂數產生訂單號碼)
	reservation.showReservation(); //顯示此次的訂桌資訊
	availTableDatabase.updateDatabase(dateCode, timeCode, customer); //更新該日的桌況
	reservationDatabase.writeInDatabase(reservation); //資料庫新增一筆訂單
}