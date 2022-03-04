#!/bin/bash

CHOICE="Y"
NB_VERTICES=$1
NB_EDGES=$2
FILENAME="instance_${NB_VERTICES}_${NB_EDGES}"

NB_INSTANCE=$3

chmod u+x maxmin.sh
for (( i=1; i<=$NB_INSTANCE; i++))
do
    ./maxmin.sh "${FILENAME}_$i.max"
    rm "${FILENAME}_$i.max"
done

exit 0
