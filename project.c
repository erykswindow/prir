#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "project_seq.h"
#include <omp.h>
#include "range.h"

int main(int argc, char * argv[] ) {
	struct range xRange, yRange;
	
	xRange.start = 0.0;
	xRange.end = 1.0;
	xRange.stepCount = atol(argv[1]);
	yRange.start = 0.0;
	yRange.end = 1.0;
	yRange.stepCount = atol(argv[2]);

	double startTime = omp_get_wtime();
	double value_s = value_seq(xRange, yRange);
	double seq_duration = omp_get_wtime() - startTime;

	printf("Value Seq: %1.20f in %f\n", value_s, seq_duration);

	return 0;
}



