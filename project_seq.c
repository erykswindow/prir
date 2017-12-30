#include "function.h"
#include "project_seq.h"

double value_seq(struct range xRange, struct range yRange) {
	double value = 0.0;
	long i,j;
	double dx = stepSize(xRange);
	double dy = stepSize(yRange);
	for(i = 0; i < xRange.stepCount; i++) {
		double x = xRange.start + (double)i * dx;
		for(j = 0; j < yRange.stepCount; j++) {
			double y = yRange.start + (double)j * dy;
			value += function(x, y) * dx * dy;
		}
	}
	return value;
}
