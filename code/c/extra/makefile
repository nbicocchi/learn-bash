CC=gcc
CFLAGS=-Wall
BINS=main

all: $(BINS)
	
clean:
	rm -rf *.o $(BINS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@
