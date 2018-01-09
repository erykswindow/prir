CC = gcc-7 -fopenmp -march=native -O2

all: project_omp.o function.o range.o
	$(CC) function.o project_omp.o range.o main.c -o executable.out

project_omp.o: function.o range.o project_omp.c project_omp.h
	$(CC) -c function.o range.o project_omp.c -o project_omp.o

range.o: range.c range.h
	$(CC) -c range.c -o range.o

function.o: function.c function.h
	$(CC) -c function.c -o function.o

clean:
	rm -f *.o executable.out




