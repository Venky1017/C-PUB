# Makefile for Public Key Generation with RIPEMD-160

CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lssl -lcrypto
SRC = ripemd160_keygen.c
OBJ = $(SRC:.c=.o)
EXEC = ripemd160_keygen

# Default target to build the executable
all: $(EXEC)

# Rule to create the executable from object files
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

# Rule to compile the source file into an object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object and executable files
clean:
	rm -f $(OBJ) $(EXEC)

# Run the program (can be used with `make run`)
run: $(EXEC)
	./$(EXEC)
