CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

SRC_DIR = src
BUILD_DIR = build
INC_DIR = include

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

TARGET = $(BUILD_DIR)/main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -rf $(BUILD_DIR)/*

run: all
	$(TARGET)

memtest:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all $(TARGET)

debug:
	gdb $(TARGET)

.PHONY: all clean run memtest debug
