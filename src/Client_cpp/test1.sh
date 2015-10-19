#!/bin/bash

if [ ! $# == 1 ]; then

echo "Usage : ./test2.sh [NodeNum]"
exit

fi

NODENUM=$1

CURTIME=`date +%s`
CURTIME=$(($CURTIME+2))

DURATION=100

KEYSIZE=1024

RANDTIME=`date +%N`
RANDTIME=$(($RANDTIME+$$))

echo $CURTIME

for i in {1..1}
do

./Benchmark $NODENUM $CURTIME $DURATION $KEYSIZE ${RANDTIME}0$i >> res &

done
