#Require a minimum version
cmake_minimum_required(VERSION 3.10)

project(uva-string)

add_library(uva-string
	${CMAKE_CURRENT_LIST_DIR}/src/string.cpp
)

include_directories(${CMAKE_CURRENT_LIST_DIR})

#Tests

#Create tests for parent project
cspec_configure("uva-string" ${CMAKE_CURRENT_LIST_DIR} "uva-string")