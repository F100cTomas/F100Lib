#ifndef F100LIB_HPP
#define F100LIB_HPP
#include <cstddef>
#include <cstdlib>
#include <cstring>
namespace F100Lib {
class CString;
constexpr size_t strlen(const char* str) { return (*str) ? 1 + strlen(str + 1) : 0; }
class CString {
  char* data;
public:
  constexpr CString(void) : data(nullptr) {}
  constexpr CString(char* str) : data(str) {}
  constexpr CString(const CString& str) : data(str.data) {}
  inline CString(size_t length) : data(new char[length + 1]) {}
  inline ~CString() {}
public:
  constexpr operator char*() { return data; }
  constexpr operator const char*() const { return data; }
public:
  class SizedCString {
    char*  data;
    size_t size;
  public:
    constexpr SizedCString(char* s, size_t l) : data(s), size(l) {}
  public:
    inline void copy_from(const CString str) {
      size_t i = 0;
      while (i < size && str.data[i] != '\0') {
        data[i] = str.data[i];
        i++;
      }
      data[i] = '\0';
    }
  };
  constexpr SizedCString of_size(size_t size) { return SizedCString(data, size); }
public:
  inline CString copy() {
    size_t length = strlen(data);
    char*  out    = new char[length + 1];
    for (size_t i = 0; i < length; i++) out[i] = data[i];
    out[length] = '\0';
    return out;
  }
  inline CString move() {
    char* out{data};
    data = nullptr;
    return out;
  }
  inline void           free() { delete[] data; }
  constexpr size_t      length() const { return strlen(data); }
  constexpr const char* get() const { return data; }
public:
  inline bool operator==(const CString str) const { return strcmp(data, str) == 0; }
  inline bool operator!=(const CString str) const { return strcmp(data, str) != 0; }
  inline bool operator>=(const CString str) const { return strcmp(data, str) >= 0; }
  inline bool operator<=(const CString str) const { return strcmp(data, str) <= 0; }
  inline bool operator>(const CString str) const { return strcmp(data, str) > 0; }
  inline bool operator<(const CString str) const { return strcmp(data, str) < 0; }
};
} // namespace F100Lib
#endif
