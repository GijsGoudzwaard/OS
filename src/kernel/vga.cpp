#include "../headers/vga.h"
#include "../headers/string.h"
#include "../headers/common.h"
#include "../headers/colors.h"
#include <stdarg.h>

/**
 * Each character takes up two bytes of space in memory.
 * The first byte is split into two segments, the forecolour, and the backcolour.
 * The second byte is a n 8-bit ASCII value of the character to print.
 *
 * @var char *
 */
char *terminal_buffer = (char *) 0xB8000;

const int VGA_WIDTH = 80;
const int VGA_HEIGHT = 25;

int row = 0;
int col = 0;

/**
 * Put a character at a specific location in video memory.
 *
 * @param  char c
 * @param  int color
 * @param  int x
 * @param  int y
 * @return void
 */
void putch(char c, int color, int x, int y)
{
  int mem_location = (y * VGA_WIDTH + x) * 2;

  terminal_buffer[mem_location] = (char) (c | 0x0f << 8);
  terminal_buffer[++mem_location] = (char) color;

  // Check if we're at the end of the terminal.
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
void set_cursor(int x, int y)
{
  int position = (y * VGA_WIDTH) + x;
  // cursor LOW port to vga INDEX register
  outb(0x3D4, 0x0F);
  outb(0x3D5, (unsigned char) (position & 0xFF));
  // cursor HIGH port to vga INDEX register
  outb(0x3D4, 0x0E);
  outb(0x3D5, (unsigned char) ((position >> 8) & 0xFF));
}

/**
 * Write a string.
 *
 * @param  int  color
 * @param  const char *string
 * @return void
 */
void write_string(int color, const char *string)
{
  while (*string != 0) {
    if (*string == '\n') {
      // New line
      row++;
      col = 0;
    } else if (*string == '\b') {
      // Backspace
      if (col > 0) {
        col--;
        putch(' ', color, col--, row);
      }
    } else if (*string == '\t') {
      uint8_t i;
      for (i = 0; i < 3; i++) {
        putch(' ', color, col + i, row);
      }
    } else {
      putch(*string, color, col, row);
    }

    string++;
  }

  set_cursor(col, row);
}

/**
 * Print a string to the terminal buffer.
 *
 * @param  const char *string
 * @return void
 */
void vga::print(const char *string)
{
  write_string(WHITE, string);
}

/**
 * Print a string to the terminal buffer and add a new line afterwards.
 *
 * @param  const char *string
 * @return void
 */
void vga::println(const char *string)
{
  write_string(WHITE, string);

  row++;
  col = 0;

  set_cursor(col, row);
}

/**
 * Prints a formatted output to VGA buffer.
 * Supports %s and %c at the moment.
 *
 * @param const char *format
 * @param ...
 */
void vga::printf(const char *format, ...)
{
  va_list arg;
  va_start(arg, format);

  while (*format != 0) {
    if (*format == '%') {
      char type = *(++format);

      switch (type) {
        case 'c': {
          int c = va_arg(arg, int);
          putch((char) c, WHITE, col, row);

          break;
        }
        case 's': {
          char *s = va_arg(arg, char *);
          vga::print(s);

          break;
        }
        default:
          break;
      }

      format++;
      continue;
    }

    putch(*format, WHITE, col, row);
    format++;
    set_cursor(col, row);
  }

  va_end(arg);
}

/**
 * Clear the screen of default text by emulators.
 *
 * @param  int color
 * @return void
 */
void vga::clear_screen(int color)
{
  for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
    terminal_buffer[i++] = ' ';
    terminal_buffer[i] = (char) color;
  }

  row = 0;
  col = 0;

  set_cursor(row, col);
}

/**
 * Set the welcome screen.
 *
 * @return void
 */
void welcome_screen()
{
  vga::println(" ____________________________________");
  vga::println("< Welcome to Aperture Science, GLaDOS >");
  vga::println(" ------------------------------------");
  vga::println("        \\   ^__^");
  vga::println("         \\  (oo)\\_______");
  vga::println("            (__)\\       )\\/\\");
  vga::println("                ||----w |");
  vga::println("                ||     ||");
}

void vga::setup()
{
  // Clear the default text that is set in qemu.
  // TODO: Set the color parameter to the default background color.
  clear_screen(WHITE);

  // Show the welcome screen.
  welcome_screen();
}
