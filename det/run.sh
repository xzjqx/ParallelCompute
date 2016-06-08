#!/bin/bash
echo "##########################"
echo "#    Serial Algorithm    #"
echo "##########################"

for i in $(seq 1 10 ) ;
do
	echo "#Round $i";
	./det 12 det12;
done

for i in $(seq 1 12 ) ;
do
	echo "##########################"
	echo "#   Parallel Algorithm   #"
	echo "#       $i Threads       #"
	echo "##########################"

	for j in $(seq 1 10 ) ;
	do
	        echo "#Round $j";
		./det_c 12 det12 $i;
	done
done

