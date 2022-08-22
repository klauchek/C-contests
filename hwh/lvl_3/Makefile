CC = gcc
override CFLAGS += -c
OPTIMISATION = -O3

all: hwh clean

hwh: main.o hashtable.o strs_pair.o
	$(CC) main.o hashtable.o strs_pair.o -o hwh_lvl_3

strs_pair.o: strs_pair/strs_pair.c
	$(CC) $(CFLAGS) $(OPTIMISATION) strs_pair/strs_pair.c

hashtable.o: ../hashtable/hashtable.c
	$(CC) $(CFLAGS) $(OPTIMISATION) ../hashtable/hashtable.c
	
main.o: main.c
	$(CC) $(CFLAGS) $(OPTIMISATION) main.c

clean:
	rm -rf *.o hwh