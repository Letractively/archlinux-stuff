#!/bin/sh

EMAIL=email@domain.org

if [ `basename $1` == "echat-msg.log" ]; then
	if [ `echo $2 | grep "message from" | wc -l` -ne 0 ]; then
		echo -n 1 >~/echat-sms.dat
		exit 0
	fi
	if [ `cat ~/echat-sms.dat` -eq 1 ]; then
		DATE=`date "+%Y.%m.%d.%H.%M.%S"`
		tail -n -4 $1 | perl -ne " \
			s/\[.*\] message from//g; s/\[.*\] autoanswer from .*//g; \
	    	s/\[.*\] message to/2/g; \
		    s/�/A/g; s/�/B/g; s/�/W/g; s/�/G/g; s/�/D/g; s/�/E/g; s/�/YO/g; s/�/ZH/g; \
		    s/�/Z/g; s/�/I/g; s/�/J/g; s/�/K/g; s/�/L/g; s/�/M/g; s/�/N/g; s/�/O/g; \
		    s/�/P/g; s/�/R/g; s/�/S/g; s/�/T/g; s/�/U/g; s/�/F/g; s/�/KH/g; s/�/C/g; \
		    s/�/CH/g; s/�/SH/g; s/�/SCH/g; s/�//g; s/�/Y/g; s/�//g; s/�/E/g; s/�/YU/g; \
		    s/�/YA/g; s/�/a/g; s/�/b/g; s/�/w/g; s/�/g/g; s/�/d/g; s/�/e/g; s/�/yo/g; \
		    s/�/zh/g; s/�/z/g; s/�/i/g; s/�/j/g; s/�/k/g; s/�/l/g; s/�/m/g; s/�/n/g; \
		    s/�/o/g; s/�/p/g; s/�/r/g; s/�/s/g; s/�/t/g; s/�/u/g; s/�/f/g; s/�/kh/g; \
		    s/�/c/g; s/�/ch/g; s/�/sh/g; s/�/sch/g; s/�//g; s/�/y/g; s/�//g; s/�/e/g; \
		    s/�/yu/g; s/�/ya/g; print; \
			" | mail -s "echat-$DATE" $EMAIL >>~/echat-sms.log 2>>~/echat-sms.log
		echo -n 0 >~/echat-sms.dat
	fi
fi
