#include <climits>
#include "Date.h"

using namespace std;

unique_ptr<Date> Date::instance{new Date()};

Date::Date(){
	month = 10;
	day = 21;
	year = 2015;
	addSecondsInDay = 60 * 60 * 24;
	timer = 1445401740; 
}

Date& Date::Instance() {
    return *instance;
}

void Date::AdvanceDate(){
	
    cout << "\ntoday is: " << month << "/" << day << "/" << year << endl;
	cout <<"How many days would you like to advance:  ";
	
    int daysPlus = 0;
	
    if ( cin >> daysPlus ) {
        cin.clear();
        cin.ignore(); // '\n'
        
        DaysCheck(month,year);
        AdvanceDayMonthYear(daysPlus);
    } else {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        AdvanceDate();
    }

	cout << "today is now: " << month << "/" << day << "/" << year << endl;
    /*while(!(cin>>daysPlus)){
		cout <<daysPlus;
		cout << "You must enter a real number"<<endl;
		cin.clear(40,'\n');
		cin.ignore(INT_MAX, '\n');
		fflush(stdin);*/
		//AdvanceDate();
	//}
	//cout << daysPlus;
	
	//cin.ignore();
	//cin.clear(40, '\n');

}

//sets number of days in each month
void Date::DaysCheck(int myMonth, int myYear){
	//testing code
	//cout << "What month:  ";
	//int joe = 0;
	//cin >> joe;
	//month = joe;
	if ((myMonth < 8 && myMonth % 2 == 1) || (myMonth >7 && myMonth % 2 == 0)){
		daysInMonth = 31;
	}
	else if (myMonth == 2){
		if (myYear % 4 == 0){
			daysInMonth = 29;
		}
		else
		daysInMonth = 28;
	}
	else{
		daysInMonth = 30;
	}
	//testing code
	//cout <<month << "/" <<day<< "/" << year << endl;
	//cout << "days in month: " << daysInMonth << endl;
}

void Date::AdvanceDayMonthYear(int plusDays)
{
	while (plusDays > 0){
		while (day < daysInMonth && plusDays >0){
			day++;
			plusDays--;
			timer = timer + addSecondsInDay;
		}
		if (plusDays > 0 && month < 12){
			month++;
			day = 1;
			plusDays--;
			timer = timer + addSecondsInDay;
			DaysCheck(month,year);
		}
		if (day == daysInMonth && plusDays> 0 && month == 12){
			year++;
			month = 1;
			day = 1;
			plusDays--;
			timer = timer + addSecondsInDay;
		}
	}
	//cout <<"today is now: "<<month << "/" <<day<< "/" << year << endl;
}

string Date::TodaysDateIs(){
	string today = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
	return (today);
}
time_t Date::TodayIs(){

	TodaysDateIs();
	return (timer);
}
string Date::convertTime_tToString(time_t TimeStampSent){
	string timeToString="";
	time_t findStringTimeStamp = 1445385599;
	int findStringDay = 20;
	int findStringMonth = 10;
	int findStringYear = 2015;

	DaysCheck(findStringMonth,findStringYear);
	while (findStringTimeStamp < TimeStampSent){
		while (findStringDay < daysInMonth && TimeStampSent >= findStringTimeStamp){
			findStringTimeStamp = findStringTimeStamp + addSecondsInDay;
			findStringDay++;
		}
		if (findStringDay == daysInMonth && findStringMonth < 12 && findStringTimeStamp <TimeStampSent){
			findStringMonth++;
			findStringDay = 1;
			findStringTimeStamp = findStringTimeStamp + addSecondsInDay;
			DaysCheck(findStringMonth,findStringYear);
		}
		if (findStringMonth == 12 && findStringTimeStamp < TimeStampSent && findStringDay == daysInMonth){
			findStringYear++;
			findStringMonth = 1;
			findStringDay = 1;
			findStringTimeStamp = findStringTimeStamp + addSecondsInDay;
		}
	}
	timeToString = (to_string(findStringDay)) + "/" + (to_string(findStringMonth)) + "/" + (to_string(findStringYear));
	return(timeToString);
}
