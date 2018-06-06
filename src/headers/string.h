#ifndef OS_STRING_H
#define OS_STRING_H

namespace string
{
  int compare(const char *string1, const char *string2);

  int length(const char *string);

  void append(char *string, char character);
};

#endif // OS_STRING_H
