#ifndef RANGE_H
#define RANGE_H

struct range {
	double start;
	double end;
	long stepCount;
};

double stepSize(struct range aRange);

#endif // RANGE_H
