#!/bin/bash

make clean
make

cat test0-pkts.in | ./firewall.sh test0-rules.in > out.txt

diff out.txt test0-pkts.cmp

cat test1-pkts.in | ./firewall.sh test1-rules.in > out.txt

diff out.txt test1-pkts.cmp

cat test2-pkts.in | ./firewall.sh test2-rules.in > out.txt

diff out.txt test2-pkts.cmp

cat test3-pkts.in | ./firewall.sh test3-rules.in > out.txt

diff out.txt test3-pkts.cmp
