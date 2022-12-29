CC = gcc
CFLAGS = -g -Wall

all: isort txtfind

isort: main_partA.o isort.o insertionheader.h
	$(CC) $(FLAGS) isort.o main_partA.o -o isort

txtfind: txtfind.o
	$(CC) $(FLAGS) txtfind.o -o txtfind

clean:
	rm txtfind isort *.o 