#ifndef VGA_H
#define VGA_H

namespace vga
{
    void setup();

    void clear_screen(int color);

    void printf(const char *format, ...);
};

#endif