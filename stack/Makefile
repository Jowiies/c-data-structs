CC = gcc
CFLAGS = -Wall -Wextra -O2 -g -std=c11 

all: program

# Stack -> libstack
libstack.a: Stack.o
	ar rcs libstack.a Stack.o 

# Stack.c -> Stack.o
Stack.o : Stack.c 
	$(CC) $(CFLAGS) -c Stack.c -o Stack.o

program : main.o libstack.a
	$(CC) $(CFLAGS) -o program main.o -L. -lstack

main.o : main.c Stack.h
	$(CC) $(CFLAGS) -c main.c -o main.o

clean:
	rm -f *.o *.a program
