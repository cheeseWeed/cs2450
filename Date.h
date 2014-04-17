#ifndef __Library__Date__
#define __Library__Date__

#include <memory>
#include <string>
#include <iostream>
#include <time.h>

class Date{

private:
    static std::unique_ptr<Date> instance;
	time_t timer;
	long int timestamp;
	int addSeconds;
	int day;
	int month;
	int year;
	int daysInMonth;
	void DaysCheck();
	void AdvanceDayMonthYear(int);

    Date();
public:
	std::string TodaysDateIs();
    static Date& Instance();
	void AdvanceDate();
	time_t TodayIs();

};

#endif /* defined(__Library__Date__) */

