CC = gcc
CFLAGS = -Wall -g
LIBS = -lssl -lcrypto

# Default target
all: public_key

public_key: public_key.c
	$(CC) $(CFLAGS) -o public_key public_key.c $(LIBS)

# Clean up compiled files
clean:
	rm -f public_key
