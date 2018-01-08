#include "function.h"
#include "project_omp.h"
#include <omp.h>
#include <math.h>
#include <stdio.h>

double value_omp(struct range xRange, struct range yRange, int threads) {
	double value = 0.0;
	double dx = stepSize(xRange);
	double dy = stepSize(yRange);
	int chunk = xRange.stepCount/threads;
	
	#pragma omp parallel for num_threads(threads) schedule(static, chunk) reduction(+:value)
	for(long i = 0; i < xRange.stepCount; i++) {
		double x = xRange.start + (double)i * dx;
		double stepValue = 0.0;
		for(long j = 0; j < yRange.stepCount; j++) {
			double y = yRange.start + (double)j * dy;
			stepValue += function(x, y) * dx * dy;
		}

		value += stepValue;
	}
	return value;
}