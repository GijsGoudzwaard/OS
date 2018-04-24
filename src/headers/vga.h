#ifndef VGA_H
#define VGA_H

namespace vga
{
  void setup();

  void clear_screen(int color);

  void print(const char *string);

  void println(const char *string);

  void print_center(char *string);

  void set_default_cursor_location();
};

#endif