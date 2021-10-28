#include "MACVendor.h"
#include <iostream>

using namespace std;

MACVendorDB::MACVendorDB(){


}
 
const pair<string, string> MACVendorDB::empty_pair;

uint64_t string_to_uint64(string& str_mac){

		uint64_t mac;
		str_mac.erase(remove_if(str_mac.begin(), str_mac.end(), [](unsigned char delim) {return delim == ':' || delim == '-' || delim == '.'; }), str_mac.end());

		stringstream iss(str_mac);

		iss >> hex >> mac;

		return mac;

}

bool MACVendorDB::loadFile(string filename){

	MAcDiap MD;
	bool success = false;

	ifstream in;

	string line;

	in.open(filename);

	if (!in) {

		return success;
	}

	else
	{
		success = true;

		while (getline(in, line)) {
			
			
			string mac_line = line.substr(0, line.find("\t"));

			auto secondBegin = line.find_first_not_of("\t", mac_line.length());
			auto secondEnd = line.find_first_of("\t", line.find_first_not_of("\t", mac_line.length()));

			MD.vendorNames.first = line.substr(secondBegin, secondEnd - secondBegin);

			auto thirdBegin = line.find_first_not_of("\t", secondEnd);
			auto thirdEnd = line.find_first_of("\t", thirdBegin);

			if (secondEnd == string::npos || thirdBegin == line.find('#')) {

				MD.vendorNames.second = "";
			}

			else{

				MD.vendorNames.second = line.substr(thirdBegin, thirdEnd - thirdBegin);

			}


				if (mac_line.find("/") != string::npos) {


					stringstream ss;

					string str_mask = mac_line.substr(mac_line.find("/") + 1);
					ss << str_mask;

					uint64_t mask;
					ss >> mask;
					mac_line = mac_line.substr(0, mac_line.find("/", 0));

					uint64_t lomask = 0xFFFFFFFFFFFFull >> mask;
					uint64_t himask = ~lomask;

					string_to_uint64(mac_line);

					MD.from = string_to_uint64(mac_line) & himask;
					MD.to = MD.from + lomask;
					mp_mac[MD.to] = MD;
				}

				else {

					MD.from = string_to_uint64(mac_line) * 0x1000000;
					MD.to = MD.from + 0xFFFFFF;
					mp_mac[MD.to] = MD;
				}
		}
		
		return success;
	}

}



pair<string,string> MACVendorDB::findVendor(const uint64_t& user_mac){

	map<uint64_t, MAcDiap> ::iterator it = mp_mac.begin();

	it = mp_mac.lower_bound(user_mac);

	if (it != mp_mac.end() && user_mac >= it->second.from && user_mac <= it->second.to) {


		return it->second.vendorNames;
	}

	else {

		return empty_pair;
	}
	
}







