#include "../headers/vga.h"
#include "../headers/string.h"
#include "../headers/common.h"
#include "../headers/colors.h"
#include "../headers/integer.h"
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
                    vga::printf(s);

                    break;
                }
                case 'd': {
                    int d = va_arg(arg, int);
                    vga::printf(integer::to_ascii(d));

                    break;
                }
                default:
                    // Print '%' when it can't find a type.
                    // If so it will just be a '%' in the string.
                    putch('%', WHITE, col, row);
                    break;
            }

            format++;
            continue;
        }

        if (*format == '\n') {
            // New line
            row++;
            col = 0;
        } else if (*format == '\b') {
            // Backspace
            if (col > 0) {
                col--;
                putch(' ', WHITE, col--, row);
            }
        } else if (*format == '\t') {
            uint8_t i;
            for (i = 0; i < 3; i++) {
                putch(' ', WHITE, col + i, row);
            }
        } else {
            putch(*format, WHITE, col, row);
        }

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
    vga::printf(" ____________________________________\n");
    vga::printf("< Welcome to Aperture Science, GLaDOS >\n");
    vga::printf(" ------------------------------------\n");
    vga::printf("        \\   ^__^\n");
    vga::printf("         \\  (oo)\\_______\n");
    vga::printf("            (__)\\       )\\/\\\n");
    vga::printf("                ||----w |\n");
    vga::printf("                ||     ||\n");
}

void vga::setup()
{
    // Clear the default text that is set in qemu.
    // TODO: Set the color parameter to the default background color.
    clear_screen(WHITE);

    // Show the welcome screen.
    welcome_screen();
}
