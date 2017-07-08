#include "../headers/vga.h"
#include "../headers/colors.h"

char *terminal_buffer = (char*) 0xB8000;

const int VGA_WIDTH = 80;
const int VGA_HEIGHT = 25;

int row = 0;
int col = 0;

void putchar(char *string, int color, int y, int x)
{
  int mem_location = (y * VGA_WIDTH + x) * 2;

  terminal_buffer[mem_location] = *string;
  terminal_buffer[++mem_location] = color;

  // Check if we're at the end of th terminal.
  if (++col == VGA_WIDTH) {
    // If so set the col back to 0 and add a new line.
    col = 0;
    row++;
  }
}

void write_string(int color, char *string)
{
  while (*string != 0) {
    if (*string == '\n') {
      row++;
      col = 0;
    } else {
      putchar(string, color, row, col);
    }

    string++;
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

  row++;
  col = 0;
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