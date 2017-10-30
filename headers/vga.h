#ifndef VGA_H
#define VGA_H

void clear_screen(int color);

void print(char *string);

void println(char *string);

void enable_cursor();

void welcome_screen();

void set_default_cursor_location();

#endif