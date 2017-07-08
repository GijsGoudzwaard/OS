#include "../headers/stdio.h"

int strlen(char *string) {
  int length = 0;

  while (string[length] != 0) {
    length++;
  }

  return length;
}