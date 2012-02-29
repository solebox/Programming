#!/bin/sh
#made by Sole :) all rights reserved
if [ $# -ne 1 ]
	then
	echo "Usage: $0 <subnet>"
	echo "ex: $0 192.168.1"
	exit 65
fi
for ip in `seq 1 254`;do
	ping -c 1 $1.$ip |grep -i 'bytes from' |cut -d " " -f4 |cut -d":" -f1 |sort&
	done

	arp -a |grep "]"
