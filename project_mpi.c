#include "function.h"
#include "project_mpi.h"
#include <stdio.h>

double value_mpi(struct range xRange, struct range yRange, int procid, int numprocs) {
	double value = 0.0;
	double dx = stepSize(xRange);
	double dy = stepSize(yRange);

	int start = procid;

	for(long i = start; i < xRange.stepCount; i = i + numprocs) {
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