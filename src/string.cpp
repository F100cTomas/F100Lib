#include <iostream>
#include "F100Lib.hpp"
namespace F100Lib {
void SizedStringRef::operator+=(const StringRef str) {
  size_t diff = length();
  size_t i    = 0;
  for (; diff + i < buffSize; i++) {
    char c         = str[i];
    buff[diff + i] = c;
    if (c == '\0') return;
  }
  buff[buffSize - 1] = '\0';
}
}
