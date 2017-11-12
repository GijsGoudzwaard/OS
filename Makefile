CC = i686-elf-gcc
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Woverflow -m32
LD = $(CC) -T linker.ld
LDFLAGS = -ffreestanding -O2 -nostdlib -lgcc
TARGET = os_image.bin
EMULATOR = qemu-system-i386

# Find all files with a .s or .c extension
OBJECTS = $(patsubst %.c, %.o, $(shell find . -name "*.c" -or -name "*.s"))

all: $(TARGET)

$(TARGET): $(OBJECTS)
  # Link all the objects together
	$(LD) -o $@ $(LDFLAGS) $^

  # After we have our os image, delete all the object files to clean the project up
	find . -name "*.o" -type f -delete

# You don't even need to be explicit here,
# compiling C files is handled automagically by Make.
%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

# Clean the project of object files.
clean:
	find . -name "*.o" -type f -delete

# Compile, clean and run the project.
run: all clean
	$(EMULATOR) -kernel ./os_image.bin
