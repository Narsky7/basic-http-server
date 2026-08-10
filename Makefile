### LLM slop makefile
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Isrc

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Output executable name
TARGET = $(BIN_DIR)/server

# Find all .c files in src/ and define corresponding .o files in obj/
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Default target: compile and run
.PHONY: all
all: run

# Run target depends on the compiled executable
.PHONY: run
run: $(TARGET)
	@echo "=== Running $(TARGET) ==="
	@./$(TARGET)

# Rule to link the object files into the final executable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Rule to compile .c files into .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
.PHONY: clean
clean:
	@echo "Cleaning up..."
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/*
