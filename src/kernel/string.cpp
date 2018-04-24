#include "../headers/string.h"

/**
 * Checks if a string is equal to another string.
 *
 * @param  const char *s1
 * @param  const char *s2
 * @return int
 */
int string::compare(const char *string1, const char *string2)
{
  while (*string1 != '\0' && *string1 == *string2) {
    ++string1;
    ++string2;
  }

  if (*string1 == *string2) {
    return 0;
  }

  return *string1 < *string2 ? -1 : 1;
}

/**
 * Count the length of a string and return it.
 *
 * @return int
 */
int string::length(char *string)
{
  int length = 0;

  while (string[length] != 0)
    length++;

  return length;
}

/**
 * Append a character to a string.
 *
 * @param char *string
 * @param char character
 */
void string::append(char *string, char character)
{
  int len = string::length(string);

  string[len] = character;
  string[len + 1] = '\0';
}