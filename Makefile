all:
	g++ -g -Wall passthrough_hp.cc `pkg-config fuse3 --cflags --libs` -o RansomwareGateway