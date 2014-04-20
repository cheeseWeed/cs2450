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

	Library lib("library_file_test.ldb");
	Date::Instance().AdvanceDate(5);
	try{
		lib.checkout(1, 1);
		assert("testCheckout", true);
	}
	catch (exception e){
		assert("testCheckout", false);
	}
	try{
		lib.checkout(1, 99);
		assert("testCheckoutFail", false);
	}
	catch (exception e){
		assert("testCheckoutFail", true);
	}
	lib.checkin(1);
	lib.validItemId(99);
	lib.listItems(ss, ItemSearchOverdue);

	ss.str(std::string()); // clear ss
	lib.listItems(ss, ItemSearchAll);
	output = ss.str();
	assert("List All Items", output.find("Jurassic Park"));
	int count = 0;
	while (getline(ss, output))
	{
		count++;
	}
	assert("List All Items Count", count == 13)

		lib.checkin(1);
	lib.listPatronItems(ss, 1);
	lib.listAllPatrons(ss);
	lib.validPatronId(1);

	cout << endl;

	system("PAUSE");

	return 0;
}