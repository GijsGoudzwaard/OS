#ifndef VGA_H
#define VGA_H

namespace vga
{
  void setup();

  void clear_screen(int color);

  void print(const char *string);

  void printf(const char *format, ...);

  void println(const char *string);
};

#endif