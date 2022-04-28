CC=gcc
CFLAGS=-c

all: hwh clean

hwh: main.o hwh.o
	$(CC) main.o hwh.o -o HWH

hwh.o: hwh.c
	$(CC) $(CFLAGS) hwh.c
	
main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm -rf *.o hwh