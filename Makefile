CC = gcc
CFLAGS = -fno-stack-protector -m32
LD = ld $(LDFLAGS) -T linker.ld
LDFLAGS = -m elf_i386
TARGET = os_image.bin
EMULATOR = qemu-system-i386

# Find all files with a .s or .c extension
OBJECTS = $(patsubst %.c, %.o, $(shell find ./src -name "*.c"))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	nasm -f elf32 -o kernel.o kernel.asm

 	# Link all the objects together
	$(LD) -o $@ kernel.o $^

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
