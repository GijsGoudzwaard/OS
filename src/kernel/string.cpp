#include "../headers/string.h"

/**
 * Compares two strings, returns 0 if they are equal, 1 of string1 is bigger than string2 and -1 otherwise
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
        return string::STATUS_EQUAL;
    }

    return *string1 < *string2 ? string::STATUS_SMALLER : string::STATUS_BIGGER;
}

/**
 * Count the length of a string and return it.
 *
 * @param  const char *string
 * @return int
 */
int string::length(const char *string)
{
    int length = 0;

    while (string[length] != 0)
        length++;

    return length;
}

/**
 * Append a character to a string.
 *
 * @param  char *string
 * @param  char character
 * @return void
 */
void string::append(char *string, char character)
{
    int len = string::length(string);

    string[len] = character;
    string[len + 1] = '\0';
}