#include "function.h"
#include "project_omp.h"
#include <omp.h>
#include <math.h>
#include <stdio.h>

double value_omp(struct range xRange, struct range yRange) {
	double value = 0.0;
	double dx = stepSize(xRange);
	double dy = stepSize(yRange);

	omp_set_nested(1);

	#pragma omp parallel num_threads(4)
	{
		int	threadsCountX = omp_get_num_threads();
		int threadNumberX = omp_get_thread_num();
		int batchSizeX = xRange.stepCount/threadsCountX;
		long i;

		for(i = threadNumberX * batchSizeX; i < (threadNumberX + 1) * batchSizeX; i++) {
			double x = xRange.start + (double)i * dx;
			#pragma omp parallel num_threads(4)
			{
				int	threadsCountY = omp_get_num_threads();
				int threadNumberY = omp_get_thread_num();
				int batchSizeY = yRange.stepCount/threadsCountY;

				double stepValue = 0.0;
				long j;
				for(j = threadNumberY * batchSizeY; j < (threadNumberY + 1) * batchSizeY; j++) {
					double y = yRange.start + (double)j * dy;
					stepValue += function(x, y) * dx * dy;
				}
				
				#pragma omp critical 
				{
					value += stepValue;
				}
			}
		}
	}

	
	return value;
}