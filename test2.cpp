#include<catch2.hpp>
#include "MACVendor.h"


TEST_CASE("String without long vendor name") {

    MACVendorDB db;

    uint64_t mac = 0x000013000000;

    CHECK(db.loadFile("D:/manuf") == true);

    CHECK(db.findVendor(mac).first == "Camex");
    CHECK(db.findVendor(mac).second == "");
}

TEST_CASE("Line containing a comment") {

    MACVendorDB db1;

    uint64_t mac1 = 0x0000BB000000;

    CHECK(db1.loadFile("D:/manuf") == true);

    CHECK(db1.findVendor(mac1).first == "Tri-Data");
    CHECK(db1.findVendor(mac1).second == "TRI-DATA Systems Inc.");
}

TEST_CASE("Long vendor name found correctly, but without the last dot") {

    MACVendorDB db2;

    uint64_t mac2 = 0x0004FD000000;

    CHECK(db2.loadFile("D:/manuf") == true);

    CHECK(db2.findVendor(mac2).first == "JapanCon");
    CHECK(db2.findVendor(mac2).second == "Japan Control Engineering Co., Ltd.");

}

TEST_CASE("Search for a non-existent MAC address"){

    MACVendorDB db3;

    uint64_t mac3 = 0xFCD300000000;

    CHECK(db3.loadFile("D:/manuf") == true);

    CHECK(db3.findVendor(mac3).first == "");
    CHECK(db3.findVendor(mac3).second == "");

}

TEST_CASE("Open non-existent file") {

    MACVendorDB db4;

    uint64_t mac4 = 0xFCD300000000;

    CHECK(db4.loadFile("D:/non_existent_file") == false);

    CHECK(db4.findVendor(mac4).first == "");
    CHECK(db4.findVendor(mac4).second == "");

}

TEST_CASE("Multiple sequential tabs") {
    MACVendorDB db5;

    CHECK(db5.loadFile("D:/manuf"));

    const uint64_t mac5 = 0x0000D1000000;

    CHECK(db5.findVendor(mac5).first == "Adaptec");
    CHECK(db5.findVendor(mac5).second == "Adaptec, Inc.");
}



