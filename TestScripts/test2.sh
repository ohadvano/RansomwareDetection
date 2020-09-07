#!/bin/sh
sudo umount /tmp/project
g++ -g -Wall passthrough_hp.cc `pkg-config fuse3 --cflags --libs` -o RansomwareGateway
./RansomwareGateway / /tmp/project &
sleep 2
cd /tmp/project/home/ohadoz
echo 'test' > test1.txt
rm test1.txt
#rm test.txt
