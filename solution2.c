#include <stddef.h>  
#include "solution.h"

int stringStat(const char *string, size_t multiplier, int *count)
{
  (*count)++;
  int len = strlen(string);
  return len * multiplier;
}
