#!/bin/bash

if [ ! $# == 1 ]; then

echo "Usage : ./TestCT.sh [NodeNum]"
exit

fi

LOOP = 100

NODENUM=$1

CURTIME=`date +%s`
CURTIME=$(($CURTIME+2))

DURATION=100

KEYSIZE=16

OPTION=0

RANDTIME=`date +%N`

echo $CURTIME
echo $RANDTIME

for i in $(seq 1 ${LOOP})
do

echo $NODENUM $CURTIME $DURATION $KEYSIZE $OPTION ${RANDTIME}

echo "./Ciphertext_throughput $NODENUM $CURTIME $DURATION $KEYSIZE $OPTION ${RANDTIME}"
./Ciphertext_throughput $NODENUM $CURTIME $DURATION $KEYSIZE $OPTION ${RANDTIME} >> OutputCT &

done

awk 'BEGIN{total=0}{total+=$1}END{print total}' OutputCT
