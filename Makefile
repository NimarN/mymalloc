CC = gcc
CFLAGS = -g -std=c99 -Wvla -Wall -fsanitize=address,undefined

mymalloctest: mymalloctest.o mymalloc.o
	$(CC) $(CFLAGS) mymalloctest.o mymalloc.o -o mymalloctest

memtest: memtest.o mymalloc.o
	$(CC) $(CFLAGS) memtest.o mymalloc.o -o memtest

mymalloc.o: mymalloc.c mymalloc.h
	$(CC) $(CFLAGS) -c mymalloc.c
	

mymalloctest.o: mymalloctest.c mymalloc.h
	$(CC) $(CFLAGS) -c mymalloctest.c

memtest.o: memtest.c mymalloc.h
	$(CC) $(CFLAGS) -c memtest.c