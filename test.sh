#!/bin/bash

make all

CURRENT_DATE=$(date +"%y-%m-%d:%H:%M:%S")
RESULTS_FILE="./results/$CURRENT_DATE/results.csv"

mkdir -p "results"
mkdir "./results/$CURRENT_DATE"

touch "$RESULTS_FILE"
# touch "$DATA_FILE"

for stepCount in 10000 20000 30000 40000 50000; do
	for threads in 1 2 4 8 16; do
		VALUE=$(./executable.out $stepCount $threads)
		RESULT="$stepCount,$threads,$VALUE"
		echo $RESULT >> "$RESULTS_FILE" 
		echo $RESULT
	done
done

./parse.py $RESULTS_FILE $CURRENT_DATE
