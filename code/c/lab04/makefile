CC=gcc
CFLAGS=-Wall -I../utils/
HEADERS=../utils/utils.h
LIBS=../utils/utils.c
BINS=es41 es42 es43 es44 es45

all: $(BINS)
	
clean:
	rm -rf *.o $(BINS)

%: %.c $(HEADERS) $(LIBS)
	$(CC) $(CFLAGS) $(LIBS) $< -o $@
