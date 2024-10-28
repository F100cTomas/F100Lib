#include "F100Lib.hpp"
#include <cmath>
#include <cstdint>
#include <cstring>
namespace F100Lib {
void SizedStringRef::operator+=(const char c) {
  size_t len = length();
  if (len == buffSize - 1) return;
  buff[len]   = c;
  buff[++len] = '\0';
}
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
void SizedStringRef::operator+=(int32_t i) {
  if (std::signbit(i)) {
    if (i == INT32_MIN) {
      *this += "-2147483648";
      return;
    }
    *this += '-';
    i     *= -1;
  }
  const size_t len = length();
  char         digits[10];
  char* const  lastDigit     = digits + sizeof(digits) - 1;
  char*        stack_pointer = lastDigit;
  while (i >= 10) {
    *(stack_pointer--)  = '0' + i % 10;
    i                  /= 10;
  }
  *(stack_pointer--)   = '0' + i % 10;
  const size_t cpySize = std::min(static_cast<size_t>(lastDigit - stack_pointer), static_cast<size_t>(buffSize - len - 1));
  std::memcpy(buff + len, stack_pointer + 1, cpySize);
  buff[len + cpySize] = '\0';
}
void SizedStringRef::operator+=(int64_t i) {
  if (std::signbit(i)) {
    if (i == INT64_MIN) {
      *this += "-9223372036854775808";
      return;
    }
    *this += '-';
    i     *= -1;
  }
  const size_t len = length();
  char         digits[19];
  char* const  lastDigit     = digits + sizeof(digits) - 1;
  char*        stack_pointer = lastDigit;
  while (i >= 10) {
    *(stack_pointer--)  = '0' + i % 10;
    i                  /= 10;
  }
  *(stack_pointer--)   = '0' + i % 10;
  const size_t cpySize = std::min(static_cast<size_t>(lastDigit - stack_pointer), static_cast<size_t>(buffSize - len - 1));
  std::memcpy(buff + len, stack_pointer + 1, cpySize);
  buff[len + cpySize] = '\0';
}
} // namespace F100Lib
