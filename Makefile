CC = gcc-7 -fopenmp

all: project_seq.o range.o
	$(CC) function.o project_seq.o range.o project.c -o executable.out

project_seq.o: function.o range.o project_seq.c project_seq.h
	$(CC) -c function.o range.o project_seq.c -o project_seq.o

range.o: range.c range.h
	$(CC) -c range.c -o range.o

function.o: function.c function.h
	$(CC) -c function.c -o function.o

clean:
	rm -f *.o executable.out




