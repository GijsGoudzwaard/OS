#ifndef VGA_H
#define VGA_H

extern char *terminal_buffer;

extern const int VGA_WIDTH;
extern const int VGA_HEIGHT;

void clear_screen(int color);

void print(char *string);

void println(char *string);

void write_string(int color, char *string);

#endif