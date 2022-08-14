CC = gcc
override CFLAGS += -c
OPTIMISATION = -O3

all: hwh clean

hwh: main.o hwh_quads.o buffer.o
	$(CC) main.o hwh_quads.o buffer.o -o hwh_lvl_3

buffer.o: text_buffer/buffer.c
	$(CC) $(CFLAGS) $(OPTIMISATION) text_buffer/buffer.c

hwh_quads.o: hwh_quads.c
	$(CC) $(CFLAGS) $(OPTIMISATION) hwh_quads.c
	
main.o: main.c
	$(CC) $(CFLAGS) $(OPTIMISATION) main.c

clean:
	rm -rf *.o hwh