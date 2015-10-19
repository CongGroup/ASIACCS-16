#!/bin/bash

if [ ! $# == 2 ]; then

echo "Usage : ./test2.sh test|get|put|cget|cput [NodeNum]"
exit

fi

NODENUM=$2
PROGNAME=$1

CURTIME=`date +%s`

CURTIME=$(($CURTIME+2))

echo $CURTIME

for i in {1..1}
do

done
