#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "project_seq.h"
#include "project_omp.h"
#include <omp.h>
#include "range.h"

int main(int argc, char ** argv) {
	struct range xRange, yRange;
	
	xRange.start = 0.0;
	xRange.end = 1.0;
	xRange.stepCount = 1000;
	yRange.start = 0.0;
	yRange.end = 1.0;
	yRange.stepCount = 1000;


	int threads = 1;

	if(argc>=2) {
		xRange.stepCount = atol(argv[1]);
		yRange.stepCount = atol(argv[1]);
	}

	if(argc>=3) {
		threads = atoi(argv[2]);
	}

	
	double startTime = omp_get_wtime();
	// double value_s = value_seq(xRange, yRange);
	// double seq_duration = omp_get_wtime() - startTime;


	double expectedValue = 1.687489821974087541773470761906894086028671673609217569182;

	startTime = omp_get_wtime();
	double value_o = value_omp(xRange, yRange, threads);
	double omp_duration = omp_get_wtime() - startTime;

	// printf("Value Sequential: %1.20f in %f\n", value_s, seq_duration);
	printf("%e,%e\n", fabs(value_o - expectedValue), omp_duration);

	return 0;
}



