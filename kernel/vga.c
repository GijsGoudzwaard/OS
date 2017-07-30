#include "../headers/vga.h"
#include "../headers/colors.h"
#include "../headers/common.h"
#include "../headers/stdio.h"

char *terminal_buffer = (char*) 0xB8000;

const int VGA_WIDTH = 80;
const int VGA_HEIGHT = 25;

int row = 0;
int col = 0;

/**
 * Put a character at a specific location in video memory.
 *
 * @return void
 */
void putchar(char *string, int color, int x, int y)
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

/**
 * Update the position of the cursor.
 *
 * @param  int x
 * @param  int y
 * @return void
 */
void update_cursor(int x, int y)
{
  unsigned short position = (y * VGA_WIDTH) + x;
  // cursor LOW port to vga INDEX register
  outb(0x3D4, 0x0F);
  outb(0x3D5, (unsigned char) (position & 0xFF));
  // cursor HIGH port to vga INDEX register
  outb(0x3D4, 0x0E);
  outb(0x3D5, (unsigned char) ((position >> 8) & 0xFF));
}

/**
 * Write a string, update the cursor after the string has been written.
 *
 * @param  int  color
 * @param  char string
 * @return void
 */
void write_string(int color, char *string)
{
  while (*string != 0) {
    if (*string == '\n') {
      row++;
      col = 0;
    } else {
      putchar(string, color, col, row);
    }

    string++;
  }

  update_cursor(col, row);
}

/**
 * Print a string to the terminal buffer.
 *
 * @param  char string
 * @return void
 */
void print(char *string)
{
	write_string(WHITE, string);
}

/**
 * Print a string to the terminal buffer and add a new line afterwards.
 *
 * @param  char string
 * @return void
 */
void println(char *string)
{
	write_string(WHITE, string);

  row++;
  col = 0;
}

/**
 * Print a string in the middle of the screen.
 *
 * @param  char string
 * @return void
 */
void print_center(char *string)
{
  int x = (VGA_WIDTH / 2) - (strlen(string) / 2);

  while (*string != 0) {
    putchar(string++, WHITE, x++, row);
  }

  row++;
}

/**
 * Clear the screen of default text by emulators.
 *
 * @param  int color
 * @return void
 */
void clear_screen(int color)
{
   for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
	   terminal_buffer[i++] = ' ';
	   terminal_buffer[i] = color;
   }

   update_cursor(row, col);
}

/**
 * Set the welcome screen.
 *
 * @return void
 */
void welcome_screen()
{
  println(" ____________________________");
  println("< Hi there, welcome to my OS >");
  println(" ----------------------------");
  println("        \\   ^__^");
  println("         \\  (oo)\\_______");
  println("            (__)\\       )\\/\\");
  println("                ||----w |");
  println("                ||     ||");

  // Add a new empty line to set the cursor under the welcome message.
  println("");
}
