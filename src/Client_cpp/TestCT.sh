#!/bin/bash

if [ ! $# == 1 ]; then

echo "Usage : ./TestCT.sh [NodeNum]"
exit

fi

LOOP=1

NODENUM=$1

CURTIME=`date +%s`
CURTIME=$(($CURTIME+2))

DURATION=5

KEYSIZE=16

OPTION=0

RANDTIME=`date +%N`

get_char()
{
        SAVEDSTTY=`stty -g`
        stty -echo
        stty raw
        dd if=/dev/tty bs=1 count=1 2> /dev/null
        stty -raw
        stty echo
        stty $SAVEDSTTY
}


echo $CURTIME
echo $RANDTIME

for i in $(seq 1 ${LOOP})
do

echo $NODENUM $CURTIME $DURATION $KEYSIZE $OPTION ${RANDTIME}

echo "./Ciphertext_throughput $NODENUM $CURTIME $DURATION $KEYSIZE $OPTION ${RANDTIME}"
./Ciphertext_throughput $NODENUM $CURTIME $DURATION $KEYSIZE $OPTION ${RANDTIME} >> OutputCT &

done

echo "Press any key to continue..."
char=`get_char`

awk 'BEGIN{total=0}{total+=$1}END{print total}' OutputCT



