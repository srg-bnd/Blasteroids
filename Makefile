# Makefile for Blasteroids
# Supports: macOS

# macOS settings
TARGET = Blasteroids

# Get linker flags from pkg-config
LDFLAGS = $(shell pkg-config --libs allegro-5 allegro_main-5 allegro_font-5)
# Get compiler flags (include paths) from pkg-config
CFLAGS_EXTRA = $(shell pkg-config --cflags allegro-5 allegro_main-5 allegro_font-5)

# Compiler (use gcc or clang)
CC = gcc
# Alternative: CC = clang

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99 $(CFLAGS_EXTRA)

# Source files
SRCS = src/main.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

# Compile source files — include Allegro headers
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	-rm -f $(OBJS) $(TARGET)

# Rebuild everything
rebuild: clean all

# Run the game after building
run: all
	./$(TARGET)

# Phony targets
.PHONY: all clean rebuild run
