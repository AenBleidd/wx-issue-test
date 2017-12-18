all: testapp

testapp: source.cpp
	g++ -std=c++14 -o testapp source.cpp `wx-config --cppflags --libs`