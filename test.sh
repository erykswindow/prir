#!/bin/bash

make all

for stepCount in 10 50 100 500 1000 5000 10000
do
	echo "Step count = $stepCount"
	./executable.out $stepCount $stepCount
done