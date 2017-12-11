#include "function.h"
#include "project_seq.h"

double value_seq(double dx, double dy, double rangeStart, double rangeEnd) {
	int i, j;
	double value = 0.0;
	for(i = 0; i < rangeEnd / dx; i++) {
		double x = (double)i * dx;
		for(j = 0; j < rangeEnd / dy; j++) {
			double y = (double)j * dy;
			value += function(x, y) * dx * dy;
		}
	}
	return value;
}
