# Compiler and flags
CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -Iinclude -g

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN     = huffman

# Source and object files
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/bitio.c \
       $(SRC_DIR)/heap.c \
       $(SRC_DIR)/huffman.c \
       $(SRC_DIR)/fileformat.c \
       $(SRC_DIR)/compressor.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Default target
all: $(BIN)

# Link
$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(BIN)

# Rebuild everything
rebuild: clean all

.PHONY: all clean rebuild
