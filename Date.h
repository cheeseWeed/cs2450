#ifndef __Library__Date__
#define __Library__Date__

#include <memory>
#include <string>
#include <iostream>

class Date{

private:
    static std::unique_ptr<Date> instance;

	int day;
	int month;
	int year;
	int daysInMonth;
	void DaysCheck();
	void AdvanceDayMonthYear(int);

    Date();
public:

    static Date& Instance();
	void AdvanceDate();
	std::string TodayIs();

};

#endif /* defined(__Library__Date__) */

