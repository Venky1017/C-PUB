CC = gcc
CFLAGS = -Wall
LIBS = -lssl -lcrypto

# Target name
TARGET = ripemd160_example

# Source file
SRC = ripemd160_example.c

# Object file
OBJ = ripemd160_example.o

# Default target
all: $(TARGET)

# Link the object file to create the executable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

# Compile source to object
$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

# Clean up build artifacts
clean:
	rm -f $(OBJ) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

