# File: /home/dell/pujith/c/cproject-1/build/Makefile

# Paths
SRC_DIR := ../src
INC_DIR := ../inc
BUILD_DIR := .

# Output
TARGET := $(BUILD_DIR)/employee_db

# Sources and Objects
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Compiler and Flags
CC := gcc
CFLAGS := -I$(INC_DIR) -Wall -Wextra

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

# Compile
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET)


