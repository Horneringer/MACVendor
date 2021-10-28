#pragma once
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

struct MAcDiap {

	uint64_t from, to;

	pair<string, string> vendorNames;

};


class MACVendorDB{

public:

	MACVendorDB();	

	bool loadFile(string filename);

	pair<string,string> findVendor(const uint64_t& user_mac);

private:
	map<uint64_t, MAcDiap> mp_mac;


protected:

	static const pair<string,string> empty_pair;

	
	
};


