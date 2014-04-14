#include "Date.h"

Date::Date(){
	Date::month = 10;
	Date::day = 21;
	Date::year = 2015;
}

void Date::AdvanceDate(){
	DateCheck();
}
void Date::DateCheck(){
	cout <<Date::day << "/" <<"month" << "/" << "year" << endl;

}