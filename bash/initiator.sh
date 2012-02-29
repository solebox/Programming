#!/bin/bash
while [ 1 ];do
        nc -w 10 -v -z solebox.no-ip.org 6789 > /dev/null 2>&1
	if [ "$?" -ne "0" ];then
                echo '' >/dev/null
        	sleep 10s
	else
		for i in `pgrep -f 'ssh '`;do
			kill -9 $i
		done
		ssh -p 6789 -NR 3333:localhost:6789 bug@solebox.no-ip.org&
        	sleep 10m
	fi
done

