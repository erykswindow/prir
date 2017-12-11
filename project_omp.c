#include "function.h"
#include "project_omp.h"
#include <omp.h>
#include <math.h>

double value_omp(double dx, double dy, double rangeStart, double rangeEnd) {
	int xCount = ceil((rangeEnd - rangeStart)/dx);
	int yCount = ceil((rangeEnd - rangeStart)/dy);
	double values[xCount][yCount];

	omp_set_num_threads(4);

	#pragma omp parallel
	{	
		int i, j;
		int threads = omp_get_num_threads();
		int threadNumber = omp_get_thread_num();
		for(i = threadNumber; i < xCount; i += threads) {
			double x = i * dx;
			for(j = 0; j < yCount; j++) {
				double y = j * dy;
				values[i][j] = function(x, y) * dx * dy;
			}
		}
	}

	int i,j;
	double value = 0.0;
	for(i = 0; i < xCount; i++) {
		for (j = 0; j < yCount; j++) {
			value += values[i][j];
		}
	}

	return value;
}