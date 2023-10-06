CC = gcc
CFLAGS = -g -std=c99 -Wvla -Wall -fsanitize=address,undefined

mymalloctest: mymalloctest.o mymalloc.o
	$(CC) $(CFLAGS) mymalloctest.o mymalloc.o -o mymalloctest

mymalloc.o: mymalloc.c mymalloc.h
	$(CC) $(CFLAGS) -c mymalloc.c
	

mymalloctest.o: mymalloctest.c mymalloc.h
	$(CC) $(CFLAGS) -c mymalloctest.c