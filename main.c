#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#include "project_mpi.h"
#include "range.h"

int main(int argc, char ** argv) {
	struct range xRange, yRange;
	int  procid, nprocs, ierr;
	double batch_value, total;
	double t1, t2; 

	xRange.start = 0.0;
	xRange.end = 1.0;
	xRange.stepCount = 1000;
	yRange.start = 0.0;
	yRange.end = 1.0;
	yRange.stepCount = 1000;

	ierr = MPI_Init(&argc, &argv);
	ierr = MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	ierr = MPI_Comm_rank(MPI_COMM_WORLD, &procid);

	if (argc >= 1) {
		xRange.stepCount = atol(argv[1]);
		yRange.stepCount = atol(argv[1]);
	}

	if (procid == 0) {
		t1 = MPI_Wtime();
	}

	batch_value = value_mpi(xRange, yRange, procid, nprocs);
	MPI_Reduce(&batch_value, &total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if (procid == 0) {
		t2 = MPI_Wtime();
		//https://www.wolframalpha.com/input/?i=integral(1%2F30+%2B+sin%5E2(1)+%2B+Si(1),+dx,+dy)+y+from+0+to+1+x+from+0+to+1
		double expectedValue = 1.687489821974087541773470761906894086028671673609217569182;
		printf("%e, %e\n", fabs(total - expectedValue), t2 - t1);
	}

	ierr = MPI_Finalize();
	return ierr;
}



