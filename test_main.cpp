#include <iostream>
#include <sstream>
#include "Library.h"
#include <limits>
#include <string>
#include <stdexcept>
#include "Date.h"
#include "Constants.h"

#define assert(x, y) { if (y) cout << "TEST SUCCESS"; else cout << "TEST FAILED"; cout << ": " << tab << x << endl; }

using namespace std;

int main(int argc, const char * argv[]) {
	string output;
	stringstream ss;

	//open file
	Library lib("library_file_test.ldb");

	//test the checkout
	try{
		lib.checkout(1, 3);
		assert("Checkout", true);
	}
	catch (exception e){
		assert("Checkout", false);
	}

	//test if checkout fail
	try{
		lib.checkout(1, 99);
		assert("Checkout Fail (bad item_id)", false);
	}
	catch (exception e){
		assert("Checkout Fail (bad item_id)", true);
	}

	//test if checkout fail
	try{
		lib.checkout(4, 1);
		assert("Checkout Fail (bad patron_id)", false);
	}
	catch (exception e){
		assert("Checkout Fail (bad patron_id)", true);
	}

	//test if checkout fail
	try{
		lib.checkout(4, 99);
		assert("Checkout Fail (bad patron_id & item_id)", false);
	}
	catch (exception e){
		assert("Checkout Fail (bad patron_id & item_id)", true);
	}

	//test advance date
	cout << Date::Instance().TodaysDateIs() << endl << " Advancing date +8 days." << endl;
	Date::Instance().AdvanceDate(8);
	cout << Date::Instance().TodaysDateIs() << endl;

	//test if item id is valid
		if (lib.validItemId(10) == 1){
			assert("Valid item_id", true);
		}
		else{
			assert("Valid item_id", false);
		}

	//test if item id is valid
		if (lib.validItemId(99) == 0){
			assert("Invalid item_id", true);
		}
		else{
			assert("Invalid item_id", false);
		}

	// test if overdue items list is correct
	ss.str(std::string()); // clear ss
	lib.listItems(ss, ItemSearchOverdue);
	output = ss.str();
	assert("List Overdue Items", output.find("Ender\'s Game") != string::npos && output.find("Xenocide") == string::npos);
    
	//test the items in the list
	ss.str(std::string()); // clear ss
	lib.listItems(ss, ItemSearchAll);
	output = ss.str();
	assert("List All Items", output.find("Jurassic Park") != string::npos);

	//test the number of items in the list
	int count = 0;
	while (getline(ss, output))
	{
		count++;
	}
    ss.clear();
	assert("List All Items (by line count)", count == 13)


    //test list items that a patron has
	ss.str(std::string()); // clear ss
	lib.listPatronItems(ss, 1);
	output = ss.str();
	assert("List Patron Items", output.find("Jurassic Park") != string::npos);

	//list all patrons
	ss.str(std::string());
	lib.listAllPatrons(ss);
	output = ss.str();
	assert("List Patrons", output.find("Dan") != string::npos);

	//checks patrons id
	if (lib.validPatronId(1) == 1){
		assert("Valid patron_id",true);
	}
	else{
		assert("Valid patron_id", false);
	}

	//checks patrons id fail
	if (lib.validPatronId(1) == 0){
		assert("Invalid patron_id", false);
	}
	else{
		assert("Invalid patron_id", true);
	}


	//test the checkin
	try{
		lib.checkin(1);
		assert("Checkin", true);
	}
	catch (exception e){

		assert("Checkin", false);
	}

	//test the checkin fail
	try{
		lib.checkin(40);
		assert("Checkin Fail", false);
	}
	catch (exception e){

		assert("Checkin Fail", true);
	}
	//cout << Date::Instance().TodaysDateIs() << endl;
	//cout<<Date::Instance().convertTime_tToString(Date::Instance().TodayIs())<<endl;
	if (Date::Instance().TodaysDateIs() == Date::Instance().convertTime_tToString(Date::Instance().TodayIs())){
		assert("Convert Date Time ", true);
	}
	cout << endl;

	system("PAUSE");

	return 0;
}