#!/bin/bash

CHOICE="Y"
NB_VERTICES=$1
NB_EDGES=$2
FILENAME="instance_${NB_VERTICES}_${NB_EDGES}"
UPPER_BOUND=$3

NB_INSTANCE=$4

file="log.txt"

chmod u+x random
for (( i=1; i<=$NB_INSTANCE; i++))
	do
		touch $file
		echo $CHOICE >> $file
		echo "${FILENAME}_$i" >> $file
		echo ${NB_VERTICES} >> $file
		echo ${NB_EDGES} >> $file
		echo ${UPPER_BOUND} >> $file
		./random < $file
		rm $file
done

exit 0

