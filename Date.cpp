#include "Date.h"

Date::Date(){
	month = 10;
	day = 21;
	year = 2015;
	daysInMonth;
}

void Date::AdvanceDate(){
	cout << "\ntoday is: " << month << "/" << day << "/" << year << endl;
	cout <<"How many days would you like to advance:  ";
	int daysPlus = 0;
	string number;
	getline(cin, number);
	try{
		daysPlus = stoi(number);
	}
	catch (exception){
		AdvanceDate();
	}
	/*while(!(cin>>daysPlus)){
		cout <<daysPlus;
		cout << "You must enter a real number"<<endl;
		cin.clear(40,'\n');
		cin.ignore(INT_MAX, '\n');
		fflush(stdin);*/
		//AdvanceDate();
	//}
	cout << daysPlus;
	DaysCheck();
	AdvanceDayMonthYear(daysPlus);
	//cin.ignore();
	//cin.clear(40, '\n');

}

//sets number of days in each month
void Date::DaysCheck(){
	//testing code
	//cout << "What month:  ";
	//int joe = 0;
	//cin >> joe;
	//month = joe;
	if ((month < 8 && month % 2 == 1) || (month >7 && month %2 ==0)){
		daysInMonth = 31;
	}
	else if (month == 2){
		if (year % 4 == 0){
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
		}
		if (plusDays > 0 && month < 12){
			month++;
			day = 1;
			plusDays--;
			DaysCheck();
		}
		if (day == daysInMonth && plusDays> 0 && month == 12){
			year++;
			month = 1;
			day = 1;
			plusDays--;
		}
	}
	cout <<"today is now: "<<month << "/" <<day<< "/" << year << endl;
}

string Date::TodayIs(){
	string today = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
	return (today);
}