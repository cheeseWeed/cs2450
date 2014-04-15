
//#ifndef __Date__Date__
//#define __Date__Date__
#include <string>
#include <iostream>
using namespace std;
class Date{

private:
	int day;
	int month;
	int year;
	int daysInMonth;
	void DaysCheck();
	void AdvanceDayMonthYear(int);
public:
	Date();
	void AdvanceDate();
	string TodayIs();


};