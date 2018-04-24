#ifndef VGA_H
#define VGA_H

namespace vga
{
  void clear_screen(int color);

  void print(const char *string);

  void println(const char *string);

  void welcome_screen();

  void print_center(char *string);

  void set_default_cursor_location();
};

#endif