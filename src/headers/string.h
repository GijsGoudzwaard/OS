#ifndef OS_STRING_H
#define OS_STRING_H

namespace string
{
  const int STATUS_EQUAL = 0;
  const int STATUS_BIGGER = 1;
  const int STATUS_SMALLER = -1;

  int compare(const char *string1, const char *string2);

  int length(const char *string);

  void append(char *string, char character);
};

#endif // OS_STRING_H
