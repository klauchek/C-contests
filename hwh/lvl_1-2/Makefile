CC=gcc
CFLAGS=-c

all: hwh clean

hwh: main.o hwh.o
	$(CC) main.o hwh.o -o hwh_lvl_1-2

hwh.o: hwh.c
	$(CC) $(CFLAGS) hwh.c
	
main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm -rf *.o hwh