all:
	g++ -std=c++0x -g -Wall passthrough_hp.cc `pkg-config fuse3 --cflags --libs` -o RansomwareGateway