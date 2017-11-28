#include "../headers/stdio.h"

/**
 * Count the length of a string and return it.
 *
 * @return int
 */
int strlen(char *string)
{
  int length = 0;

  while (string[length] != 0) {
    length++;
  }

  return length;
}
