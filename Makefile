all:
	g++ -Wall main.cpp src/*.cpp -o main -lnet -lpcap -std=c++11
