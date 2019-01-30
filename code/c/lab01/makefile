CC=gcc
CFLAGS=-Wall -I../utils/
HEADERS=../utils/utils.h
LIBS=../utils/utils.c
BINS=es11 es12 es13 es14 es15 es16 es17 es18 es19

all: $(BINS)
	

clean:
	rm -rf *.o $(BINS)

%: %.c $(HEADERS) $(LIBS)
	$(CC) $(CFLAGS) $(LIBS) $< -o $@
