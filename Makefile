CC = gcc
CFLAGS = -Wall -g
LIBS = -lssl -lcrypto

TARGET = generate_public_key
SRCS = generate_public_key.c

# Compile the program
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LIBS)

# Clean the compiled files
clean:
	rm -f $(TARGET)
