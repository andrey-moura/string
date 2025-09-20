#Require a minimum version
cmake_minimum_required(VERSION 3.10)

project(andy-string)

add_library(andy-string OBJECT
	${CMAKE_CURRENT_LIST_DIR}/src/string.cpp
)

include_directories(${CMAKE_CURRENT_LIST_DIR})

#Tests
if (TARGET andy-test)
    andy_tests_configure(andy-string)
endif()