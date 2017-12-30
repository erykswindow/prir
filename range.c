#include "range.h"

double stepSize(struct range aRange) {
	return (aRange.end - aRange.start) / (double)aRange.stepCount;
}