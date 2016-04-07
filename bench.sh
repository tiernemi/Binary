#!/bin/bash

echo "" > "bench.dat"
for i in `seq 1000 500 20000` ; do
	output=`./bst_test -n $i`
    dim=`echo $output | awk '{print $1}'` 
    tr=`echo $output | awk '{print $3}'` 
    tl=`echo $output | awk '{print $5}'`
	echo "$dim $tr $tl" >> "bench.dat"
done
