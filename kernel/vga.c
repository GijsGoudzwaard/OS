#include "../headers/vga.h"
#include "../headers/colors.h"

char *terminal_buffer = (char*) 0xB8000;

const int VGA_WIDTH = 80;
const int VGA_HEIGHT = 25;

int line_number = 0;

void write_string(int color, char *string)
{
  unsigned int i = 0;

	i = (line_number*80*2);

  while (*string != 0) {
    if (*string == '\n') {
      line_number++;
      i = (line_number * 80 * 2);
      string++;
    } else {
      terminal_buffer[i] = *string;
      string++;
      i++;
      terminal_buffer[i] = color;
      i++;
    }
  }
}

/**
 * Print a string to the terminal buffer.
 *
 * @return void
 */
void print(char *string)
{
	write_string(WHITE, string);
}

/**
 * Print a string to the terminal buffer and add a new line afterwards.
 *
 * @return void
 */
void println(char *string)
{
	write_string(WHITE, string);
  line_number++;
}

/**
 * Clear the screen of default text by emulators.
 *
 * @return void
 */
void clear_screen(int color)
{
   for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT * 2; i++) {
	   terminal_buffer[i++] = ' ';
	   terminal_buffer[i] = color;
   }
}