CC=gcc
CFLAGS=-c

all: hwh clean

hwh: main.o hashtable.o
	$(CC) main.o hashtable.o -o hwh_lvl_1-2

hashtable.o: ../hashtable/hashtable.c
	$(CC) $(CFLAGS) ../hashtable/hashtable.c
	
main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm -rf *.o hwh