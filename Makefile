CC = gcc
CFLAGS = -g -std=c99 -Wvla -Wall -fsanitize=address,undefined

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


mymalloctest: mymalloctest.o mymalloc.o
	$(CC) $(CFLAGS) mymalloctest.o mymalloc.o -o mymalloctest

memtest: memtest.o mymalloc.o
	$(CC) $(CFLAGS) memtest.o mymalloc.o -o memtest


memgrind: memgrind.o mymalloc.o
	$(CC) $(CFLAGS) memgrind.o mymalloc.o -o memgrind

memerrors: memerrors.o mymalloc.o
	$(CC) $(CFLAGS) memerrors.o mymalloc.o -o memerrors

memstringtest: memstringtest.o mymalloc.o
	$(CC) $(CFLAGS) memstringtest.o mymalloc.o -o memstringtest

basicMallocTests: basicMallocTests.o mymalloc.o
	$(CC) $(CFLAGS) basicMallocTests.o mymalloc.o -o basicMallocTests
clean:
	rm -f *.o memgrind memtest mymalloctest basicMallocTests memerrors memstringtest