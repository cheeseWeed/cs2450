#include <iostream>
#include <sstream>
#include "Library.h"
#include <limits>
#include <string>
#include <stdexcept>
#include "Date.h"
#include "Constants.h"

#define assert(x, y) { cout << x << ": "; if (!y) cout << "TEST FAILED"; else cout << "TEST SUCCESS"; cout << endl; }

using namespace std;

int main(int argc, const char * argv[]) {


		Library lib ("library_file.ldb");
		Date::Instance().AdvanceDate();
		try{
			lib.checkout(1, 1);
			assert("testCheckout", false);
		}
		catch (exception e){
			assert("testCheckout", true);
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
		lib.listItems(cout, ItemSearchOverdue);
		lib.listItems(cout, ItemSearchAll);
		lib.checkin(1);
		lib.listPatronItems(cout, 1);
		lib.listAllPatrons(cout);
		lib.validPatronId(1);

	return 0;
}
