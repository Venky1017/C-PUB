CC = gcc
CFLAGS = -Wall -O2
LIBS = -lssl -lcrypto

TARGET = public_key
SRC = public_key.c

# Build the target
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

# Clean the build
clean:
	rm -f $(TARGET)
