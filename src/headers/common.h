#ifndef COMMON_H
#define COMMON_H

extern "C" void outb(unsigned short port, unsigned char val);

extern "C" unsigned char inb(unsigned short port);

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

#endif
