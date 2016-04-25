all:
	g++ -Wall main.cpp src/*.cpp -o main -lnet -lpcap -lboost_regex -std=c++11
