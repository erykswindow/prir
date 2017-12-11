#include <math.h>
#include "function.h"

double function(double x, double y) {
	return sin(2 * y) + 0.1 * pow(x, 2) + cos(x * y);
}