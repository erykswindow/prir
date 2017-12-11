CC = gcc-7 -fopenmp

all: project_seq.o project_omp.o
	$(CC) function.o project_seq.o project_omp.o project.c -o executable.out

function.o: function.c function.h
	$(CC) -c function.c -o function.o

project_seq.o: function.o project_seq.c project_seq.h
	$(CC) -c function.o project_seq.c -o project_seq.o

project_openmp.o: function.o project_omp.c project_omp.h
	$(CC) -c function.o project_omp.c -o project_omp.o

clean:
	rm -f *.o executable.out




