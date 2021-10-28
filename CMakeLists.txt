cmake_minimum_required(VERSION 2.8)

project(MACVendor)

add_executable(${PROJECT_NAME} 
main.cpp 
MACVendor.h 
MACVendor.cpp
)

add_executable(TESTS
test1.cpp
test2.cpp
MACVendor.cpp
MACVendor.h
)

target_include_directories(MACVendor PUBLIC include)
target_include_directories(TESTS PUBLIC include)


