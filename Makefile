CC = gcc
CFLAGS = -g -std=c99 -Wall -fsanitize=address,undefined

memgrind: memgrind.o mymalloc.o 
	$(cc) $(CFLAGS) memgrind.o mymalloc.o -o memgrind

mymalloc.o: mymalloc.c mymalloc.h
	$(CC) $(CFLAGS) -c mymalloc.c

memgrind.o: memgrind.c mymalloc.h
	$(CC) $(CFLAGS) -c memgrind.c

