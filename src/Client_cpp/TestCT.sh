#!/bin/bash

if [ ! $# == 5 ]; then

echo "Usage : ./TestCT.sh [NodeNum] [LOOP] [OPTION] [TIME] [SEEDS]"
exit

fi


NODENUM=$1
LOOP=$2
OPTION=$3
CURTIME=$4
SEEDS=$5

DURATION=30
KEYSIZE=10
VALSIZE=1024

RANDTIME=`date +%N`+SEEDS


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

rm -f OutputCT

for i in $(seq 1 ${LOOP})
do

echo $NODENUM $CURTIME $DURATION $KEYSIZE $VALSIZE $OPTION ${RANDTIME}$i

echo "./Ciphertext_throughput $NODENUM $CURTIME $DURATION $KEYSIZE $VALSIZE $OPTION ${RANDTIME}$i"
./Ciphertext_throughput $NODENUM $CURTIME $DURATION $KEYSIZE $VALSIZE $OPTION ${RANDTIME}$i >> OutputCT &

done

echo "Press any key to continue..."
char=`get_char`

awk 'BEGIN{total=0}{total+=$1}END{print total}' OutputCT



