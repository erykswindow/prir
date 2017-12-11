#include <math.h>
#include <stdio.h>
#include "project_seq.h"
#include "project_omp.h"
#include <omp.h>

int main() {
	double dy = 10e-4;
	double dx = 10e-4;
	double rangeStart = 0.0;
	double rangeEnd = 1.0;

	double startTime = 0.0;

	startTime = omp_get_wtime();
	double value_s = value_seq(dx, dy, rangeStart, rangeEnd);
	double seq_duration = omp_get_wtime() - startTime;

	startTime = omp_get_wtime();
	double value_o = value_omp(dx, dy, rangeStart, rangeEnd);
	double omp_duration = omp_get_wtime() - startTime;

	printf("Value Seq: %1.20f in %f\n", value_s, seq_duration);
	printf("Value OpenMP: %1.20f in %f\n", value_o, omp_duration);

	return 0;
}



