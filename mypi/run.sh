#!/bin/bash
echo "---------1000000----------"
echo "##########################"
echo "#    Serial Algorithm    #"
echo "##########################"

for i in $(seq 1 10 ) ;
do
	echo "#Round $i";
	./pi 1000000;
done

for i in $(seq 1 16 ) ;
do
	echo "##########################"
	echo "#   Parallel Algorithm   #"
	echo "#       $i Threads       #"
	echo "##########################"

	for j in $(seq 1 10 ) ;
	do
	        echo "#Round $j";
		./cir_pi 1000000 $i;
	done
done

