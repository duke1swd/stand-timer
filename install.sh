#!/bin/bash
#
# OTA install of firmware
#
FW=$1
DEV=$2
if [ x$FW == x ] ; then
	echo usage 1>&2 fwinstall firmware device
	exit 1
fi

if [ x$DEV == x ] ; then
	 DEV=stand-timer-01
fi

echo uploading firmware $FW onto device $DEV
echo press enter to continue
read x
scp $FW pi@192.168.1.13:/tmp
ssh pi@192.168.1.13 ./go/bin/fwmgr -d ${DEV} -f /tmp/${FW} -u
