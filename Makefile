CC = gcc -fopenmp

a.out: project_seq.o
	$(CC) -c project_seq.o -o a.out

function.o: function.c function.h
	$(CC) -c function.c -o function.o

project_seq.o: function.o project_seq.c project_seq.h
	$(CC) -c function.o project_seq.c -o project_seq.o




