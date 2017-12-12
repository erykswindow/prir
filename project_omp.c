#include "function.h"
#include "project_omp.h"
#include <omp.h>
#include <math.h>

double value_omp(double dx, double dy, double rangeStart, double rangeEnd) {
	omp_set_num_threads(4);
	double value = 0.0;
	int i, j;
	#pragma omp parallel
	{	
		double sum = 0.0;
		for(i = 0; i < rangeEnd/dx; i++) {
			double x = i * dx;
			for(j = 0; j < rangeEnd/dy; j++) {
				double y = j * dy;
				sum += function(x, y) * dx * dy;
			}
		}
		#pragma omp critical
		value += sum;
	}

	return value;
}