#ifndef VGA_H
#define VGA_H

extern char *terminal_buffer;

extern const int VGA_WIDTH;
extern const int VGA_HEIGHT;

extern int row;
extern int col;

void clear_screen(int color);

void print(char *string);

void println(char *string);

void putchar(char *string, int color, int y, int x);

void write_string(int color, char *string);

#endif