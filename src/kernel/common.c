#include "../headers/common.h"

/**
 * Sends a 8/16/32-bit value on a I/O location.
 * The a modifier enforces val to be placed in the eax
 * register before the asm command is issued and Nd allows
 * for one-byte constant values to be assembled as constants,
 * freeing the edx register for other cases.
 *
 * @param  unsigned short port
 * @param  unsigned char  value
 * @return unsigned char
 */
void outb(unsigned short port, unsigned char value)
{
	asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

/**
 * Receives a 8/16/32-bit value from an I/O location.
 *
 * @param  unsigned short port
 * @return unsigned char
 */
unsigned char inb(unsigned short port)
{
	unsigned char value;
	asm volatile ("inb %1, %0" : "=a" (value) : "Nd" (port));

	return value;
}