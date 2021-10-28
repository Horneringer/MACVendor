#include <iostream>
#include "MACVendor.h"

using namespace std;


int main() {

	MACVendorDB db;
	uint64_t user_mac = 0x0004EC000000;
	uint64_t user_mac2 = 0x000018000000;
	uint64_t user_mac3 = 0x0004FD000000;
	
	db.loadFile("d:/manuf");

	db.findVendor(user_mac);
	db.findVendor(user_mac2);

	pair<string, string> result = db.findVendor(user_mac);
	cout << result.first << " " << result.second << endl;

	pair<string, string> result2 = db.findVendor(user_mac2);
	cout << result2.first << " " << result2.second << endl;

	pair<string,string> result3 = db.findVendor(user_mac3);
	cout << result3.first << " " << result3.second << endl;

	return 0;
}

