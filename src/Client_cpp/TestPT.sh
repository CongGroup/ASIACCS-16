#!/bin/bash

if [ ! $# == 1 ]; then

echo "Usage : ./TestCT.sh [NodeNum]"
exit

fi

LOOP=1

NODENUM=$1

CURTIME=`date +%s`
CURTIME=$(($CURTIME+10))

DURATION=20

KEYSIZE=10
VALSIZE=10

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

rm -f OutputPT

for i in $(seq 1 ${LOOP})
do

echo $NODENUM $CURTIME $DURATION $KEYSIZE $VALSIZE $OPTION ${RANDTIME}

echo "./Plaintext_cluster_throughput $NODENUM $CURTIME $DURATION $KEYSIZE $VALSIZE $OPTION ${RANDTIME}"
./Plaintext_cluster_throughput $NODENUM $CURTIME $DURATION $KEYSIZE $VALSIZE $OPTION ${RANDTIME} >> OutputPT &

done

echo "Press any key to continue..."
char=`get_char`

awk 'BEGIN{total=0}{total+=$1}END{print total}' OutputPT



