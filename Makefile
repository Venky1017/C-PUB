CC = gcc
CFLAGS = -Wall -g
LIBS = -lssl -lcrypto

TARGET = public_key_hash
SRC = public_key_hash.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)
