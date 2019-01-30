CC=gcc
CFLAGS=-Wall -I../utils/
HEADERS=../utils/utils.h
LIBS=../utils/utils.c
BINS=es31 es32 es33 es34 es35 es36 es37 es38 es39 es310 es311 es312 es313

all: $(BINS)
	
clean:
	rm -rf *.o $(BINS)

%: %.c $(HEADERS) $(LIBS)
	$(CC) $(CFLAGS) $(LIBS) $< -o $@
