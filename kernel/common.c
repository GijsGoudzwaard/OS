#include "../headers/common.h"

void outb(unsigned short port, unsigned char value)
{
    asm volatile("outb %1, %0" : : "dN" (port), "a" (value));
}

unsigned char inb(unsigned short port)
{
  unsigned char value;
  asm volatile("inb %1, %0" : "=a" (value) : "Nd" (port));

  return value;
}