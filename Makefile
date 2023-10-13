CC = gcc
CFLAGS = -g -std=c99 -Wvla -Wall -fsanitize=address,undefined

mymalloctest: mymalloctest.o mymalloc.o
	$(CC) $(CFLAGS) mymalloctest.o mymalloc.o -o mymalloctest

memtest: memtest.o mymalloc.o
	$(CC) $(CFLAGS) memtest.o mymalloc.o -o memtest

memtest.o: memtest.c mymalloc.h
	$(CC) $(CFLAGS) -c memtest.c

mymalloc.o: mymalloc.c mymalloc.h
	$(CC) $(CFLAGS) -c mymalloc.c
	

mymalloctest.o: mymalloctest.c mymalloc.h
	$(CC) $(CFLAGS) -c mymalloctest.c

memgrind: memgrind.o mymalloc.o
	$(CC) $(CFLAGS) memgrind.o mymalloc.o -o memgrind

memgrind.o: memgrind.c mymalloc.h
	$(CC) $(CFLAGS) -c memgrind.c

lltest: lltest.o mymalloc.o
	$(CC) $(CFLAGS) lltest.o mymalloc.o -o lltest

lltest.o: lltest.c mymalloc.h
	$(CC) $(CFLAGS) -c lltest.c