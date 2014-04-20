#include <iostream>
#include <sstream>
#include "Library.h"
#include <limits>
#include <string>
#include <stdexcept>
#include "Date.h"
#include "Constants.h"

#define assert(x, y) { cout << x << ": "; if (y) cout << "TEST SUCCESS"; else cout << "TEST FAILED"; cout << endl; }

using namespace std;

int main(int argc, const char * argv[]) {
	string output;
	stringstream ss;

	//open file
	Library lib("library_file_test.ldb");

	//test the checkout
	try{
		lib.checkout(1, 1);
		assert("testCheckout", true);
	}
	catch (exception e){
		assert("testCheckout", false);
	}

	//test if checkout fail
	try{
		lib.checkout(1, 99);
		assert("testCheckoutFail book id", false);
	}
	catch (exception e){
		assert("testCheckoutFail book id", true);
	}

	//test if checkout fail
	try{
		lib.checkout(4, 1);
		assert("testCheckoutFail user id", false);
	}
	catch (exception e){
		assert("testCheckoutFail user id", true);
	}

	//test if checkout fail
	try{
		lib.checkout(4, 99);
		assert("testCheckoutFail user id and book id", false);
	}
	catch (exception e){
		assert("testCheckoutFail user id and book id", true);
	}

	//test advance date
	cout << Date::Instance().TodaysDateIs() << "\nadvance date 5 days" << endl;
	Date::Instance().AdvanceDate(5);
	cout << Date::Instance().TodaysDateIs() << endl;

	//test if item id is valid
		if (lib.validItemId(10) == 1){
			assert("test item id", true);
		}
		else{
			assert("test item id", false);
		}

	//test if item id is valid
		if (lib.validItemId(99) == 0){
			assert("test item id fail", true);
		}
		else{
			assert("test item id fail", false);
		}

	//test if overdue items list is correct
	ss.str(std::string()); // clear ss
	lib.listItems(ss, ItemSearchOverdue);
	output = ss.str();
	assert("List overdue Items", output.find("Ender's Game")!= string::npos);

	//test if overdue items list is correct
	ss.str(std::string()); // clear ss
	lib.listItems(ss, ItemSearchOverdue);
	output = ss.str();
	assert("List overdue Items", output.find("Xenocide") == string::npos);

	//test the items in the list
	ss.str(std::string()); // clear ss
	lib.listItems(ss, ItemSearchAll);
	output = ss.str();
	assert("List All Items", output.find("Jurassic Park") != string::npos);

	//test the items in the list
	ss.str(std::string()); // clear ss
	lib.listItems(ss, ItemSearchAll);
	output = ss.str();
	assert("List All Items", output.find("pink floyd") == string::npos);

	//test the number of items in the list
	int count = 0;
	while (getline(ss, output))
	{
		count++;
	}
	assert("List All Items Count", count == 13)


		//test list items that a patron has
	ss.str(std::string()); // clear ss
	lib.listPatronItems(ss, 1);
	output = ss.str();
	assert("List Patron Items", output.find("Jurassic Park") != string::npos);

	//list all patrons
	ss.str(std::string());
	lib.listAllPatrons(ss);
	output = ss.str();
	assert("list patrons", output.find("Dan") != string::npos);

	//checks patrons id
	if (lib.validPatronId(1) == 1){
		assert("test patron id",true);
	}
	else{
		assert("test patron id", false);
	}

	//checks patrons id fail
	if (lib.validPatronId(1) == 0){
		assert("test patron id", false);
	}
	else{
		assert("test patron id", true);
	}


	//test the checkin
	try{
		lib.checkin(1);
		assert("test checkin", true);
	}
	catch (exception e){

		assert("test checkin", false);
	}

	//test the checkin fail
	try{
		lib.checkin(40);
		assert("test checkin fail", false);
	}
	catch (exception e){

		assert("test checkin fail", true);
	}

	cout << endl;

	system("PAUSE");

	return 0;
}