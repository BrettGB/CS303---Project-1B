/*CS303 - Project 1B
Group Members:
	Brett Barnow, Nathan Brown, Cole Cerv, Alex Norris
*/

#include "Date.h"
#include "library.h"
#include "BookNode.h"
#include "EmpNode.h"
#include "StringTokenizer.h"
#include <deque>

using namespace std;

int main() {
	Library library;

	library.add_book("Software Engineering");
	library.add_book("Chemistry");
	library.add_employee("Adam");
	library.add_employee("Sam");
	library.add_employee("Ann");
	library.circulate_book("Chemistry", Date(2015, 3, 1, DateFormat::US));
	library.circulate_book("Software Engineering", Date(2015, 4, 1, DateFormat::US));
	library.pass_on("Chemistry", Date(2015, 3, 5, DateFormat::US)); 
	//tell the next employee to pass the book on March 5, 2015
	
	library.pass_on("Chemistry", Date(2015, 3, 7, DateFormat::US));

	library.pass_on("Chemistry", Date(2015, 3, 15, DateFormat::US)); 
	//at this point in time, the system will archive the chemistry book.

	library.pass_on("Software Engineering", Date(2015, 4, 5, DateFormat::US));
	library.pass_on("Software Engineering", Date(2015, 4, 10, DateFormat::US));
	library.pass_on("Software Engineering", Date(2015, 4, 15, DateFormat::US));

}