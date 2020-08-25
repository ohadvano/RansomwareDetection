#!/bin/sh
sudo umount /tmp/project
g++ -g -Wall passthrough_hp.cc `pkg-config fuse3 --cflags --libs` -o RansomwareGateway
./RansomwareGateway / /tmp/project &
sleep 2
cd /tmp/project/home/ohadoz
echo 'test'>test1.txt
echo 'test'>test2.txt
echo 'test'>test3.txt
rm test1.txt test2.txt test3.txt
#rm test.txt
