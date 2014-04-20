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
	int addSecondsInDay;
	int day;
	int month;
	int year;
	int daysInMonth;
	void DaysCheck(int,int);
	

    Date();
public:
    void AdvanceDayMonthYear(int);
	std::string TodaysDateIs();
    static Date& Instance();
	void AdvanceDate(int);
	time_t TodayIs();
	std::string convertTime_tToString(time_t);

};

#endif /* defined(__Library__Date__) */

