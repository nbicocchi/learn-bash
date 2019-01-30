CC=gcc
CFLAGS=-Wall -I../utils/
HEADERS=../utils/utils.h
LIBS=../utils/utils.c
BINS=es21 es22 es23 es24 es25 es26 es27 es28 es29

all: $(BINS)
	
clean:
	rm -rf *.o $(BINS)

%: %.c $(HEADERS) $(LIBS)
	$(CC) $(CFLAGS) $(LIBS) $< -o $@
