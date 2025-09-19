# Makefile for Car Repair Shop Management

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -std=c99

# Source files
SRCS = main.c PPP.c

# Executable name
TARGET = programa

# Default target: build and run
all: $(TARGET)
	./$(TARGET)

# Build the executable
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

# Clean up object files and executable
clean:
	rm -f $(TARGET) *.o

