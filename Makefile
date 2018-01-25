CC = mpicc -march=native -O2

all: project_mpi.o function.o range.o
	$(CC) function.o project_mpi.o range.o main.c -o executable.out

project_omp.o: function.o range.o project_omp.c project_omp.h
	$(CC) -c function.o range.o project_omp.c -o project_omp.o

project_mpi.o: function.o range.o project_mpi.c project_mpi.h
	$(CC) -c function.o range.o project_mpi.c -o project_mpi.o

range.o: range.c range.h
	$(CC) -c range.c -o range.o

function.o: function.c function.h
	$(CC) -c function.c -o function.o

clean:
	rm -f *.o executable.out




