#include "../headers/vga.h"
#include "../headers/colors.h"

char *terminal_buffer = (char*) 0xB8000;

const int VGA_WIDTH = 80;
const int VGA_HEIGHT = 25;

void write_string(int color, char *string)
{
    while (*string != 0) {
      *terminal_buffer++ = *string++;
      *terminal_buffer++ = color;
    }
}

void print(char *string)
{
	write_string(WHITE, string);
}

void println(char *string)
{
	write_string(WHITE, string);
}

void clear_screen(int color)
{
   for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT * 2; i++) {
	   terminal_buffer[i++] = ' ';
	   terminal_buffer[i] = color;
   }
}