#include <math.h>
#include <stdio.h>

double function(double x, double y);

int main() {
	double dy = 10e-4;
	double dx = 10e-4;
	double rangeStart = 0.0;
	double rangeEnd = 1.0;
	int i, j;
	double value = 0.0;
	for(i = 0; i < rangeEnd / dx; i++) {
		double x = (double)i * dx;
		for(j = 0; j < rangeEnd / dy; j++) {
			double y = (double)j * dy;
			value += function(x, y) * dx * dy;
		}
	}

	printf("Value: %f\n", value);

	return 0;
}

double function(double x, double y) {
	return sin(2 * y) + 0.1 * pow(x, 2) + cos(x * y);
}



