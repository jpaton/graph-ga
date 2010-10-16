CC=g++

default: serial

serial: main.o
	$(CC) -o serial main.o

main.o: main.c
	$(CC) -c main.c
