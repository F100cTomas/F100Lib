#ifndef F100LIB_HPP
#define F100LIB_HPP
#include <cstddef>
#include <cstdlib>
#include <cstring>
namespace F100Lib {
// Class declaration
class StringRef;
class SizedStringRef;
// Function declaration
constexpr size_t strlen(const char* str);
// Class definition
class StringRef {
  char* buff;
public:
  constexpr StringRef(char* str);
  constexpr StringRef(const char* str);
  constexpr StringRef(const StringRef& str);
  inline ~StringRef();
public:
  constexpr             operator char*();
  constexpr             operator const char*() const;
  inline SizedStringRef of_size(size_t s);
public:
  inline void           free();
  constexpr size_t      length() const;
  constexpr const char* get() const;
public:
  constexpr char* begin();
  constexpr char* end();
public:
  inline char& operator[](size_t i);
public:
  inline bool operator==(const StringRef str) const;
  inline bool operator!=(const StringRef str) const;
  inline bool operator>=(const StringRef str) const;
  inline bool operator<=(const StringRef str) const;
  inline bool operator>(const StringRef str) const;
  inline bool operator<(const StringRef str) const;
};
class SizedStringRef {
  char*  buff;
  size_t buffSize;
public:
  constexpr SizedStringRef(char* str, size_t s);
  constexpr SizedStringRef(const SizedStringRef& str);
  inline SizedStringRef(size_t size);
  inline ~SizedStringRef();
public:
  constexpr operator char*();
  constexpr operator const char*() const;
public:
  inline void           free();
  constexpr size_t      length() const;
  constexpr size_t      size() const;
  constexpr const char* get() const;
public:
  constexpr char* begin();
  constexpr char* end();
public:
  inline char&          operator[](size_t i);
  void                  operator+=(const StringRef str);
  inline SizedStringRef operator<<(const StringRef str);
public:
  inline bool operator==(const StringRef str) const;
  inline bool operator!=(const StringRef str) const;
  inline bool operator>=(const StringRef str) const;
  inline bool operator<=(const StringRef str) const;
  inline bool operator>(const StringRef str) const;
  inline bool operator<(const StringRef str) const;
};
// Function definition
constexpr size_t strlen(const char* str) { return (*str) ? 1 + strlen(str + 1) : 0; }
// Method definition
constexpr StringRef::StringRef(char* str) : buff(str) {}
constexpr StringRef::StringRef(const char* str) : buff(const_cast<char*>(str)) {}
constexpr StringRef::StringRef(const StringRef& str) : buff(str.buff) {}
inline StringRef::~StringRef() {}
constexpr StringRef::operator char*() { return buff; }
constexpr StringRef::operator const char*() const { return buff; }
inline SizedStringRef StringRef::of_size(size_t s) { return SizedStringRef(buff, s); }
inline void           StringRef::free() { delete[] buff; }
constexpr size_t      StringRef::length() const { return strlen(buff); }
constexpr const char* StringRef::get() const { return buff; }
constexpr char*       StringRef::begin() { return buff; }
constexpr char*       StringRef::end() { return buff + length(); }
inline char&          StringRef::operator[](size_t i) { return buff[i]; }
inline bool           StringRef::operator==(const StringRef str) const { return strcmp(buff, str) == 0; }
inline bool           StringRef::operator!=(const StringRef str) const { return strcmp(buff, str) != 0; }
inline bool           StringRef::operator>=(const StringRef str) const { return strcmp(buff, str) >= 0; }
inline bool           StringRef::operator<=(const StringRef str) const { return strcmp(buff, str) <= 0; }
inline bool           StringRef::operator>(const StringRef str) const { return strcmp(buff, str) > 0; }
inline bool           StringRef::operator<(const StringRef str) const { return strcmp(buff, str) < 0; }
constexpr SizedStringRef::SizedStringRef(char* str, size_t s) : buff(str), buffSize(s) {}
constexpr SizedStringRef::SizedStringRef(const SizedStringRef& str) : buff(str.buff), buffSize(str.buffSize) {}
inline SizedStringRef::SizedStringRef(size_t size) : buff(new char[size]), buffSize(size) {
  for (size_t i = 0; i < size; i++) buff[i] = '\0';
}
inline SizedStringRef::~SizedStringRef() {}
constexpr SizedStringRef::operator char*() { return buff; }
constexpr SizedStringRef::operator const char*() const { return buff; }
inline void           SizedStringRef::free() { delete[] buff; }
constexpr size_t      SizedStringRef::length() const { return strlen(buff); }
constexpr size_t      SizedStringRef::size() const { return buffSize; }
constexpr const char* SizedStringRef::get() const { return buff; }
constexpr char*       SizedStringRef::begin() { return buff; }
constexpr char*       SizedStringRef::end() { return buff + length(); }
inline char&          SizedStringRef::operator[](size_t i) { return buff[i]; }
inline SizedStringRef SizedStringRef::operator<<(const StringRef str) {
  (*this) += str;
  return *this;
}
inline bool SizedStringRef::operator==(const StringRef str) const { return strcmp(buff, str) == 0; }
inline bool SizedStringRef::operator!=(const StringRef str) const { return strcmp(buff, str) != 0; }
inline bool SizedStringRef::operator>=(const StringRef str) const { return strcmp(buff, str) >= 0; }
inline bool SizedStringRef::operator<=(const StringRef str) const { return strcmp(buff, str) <= 0; }
inline bool SizedStringRef::operator>(const StringRef str) const { return strcmp(buff, str) > 0; }
inline bool SizedStringRef::operator<(const StringRef str) const { return strcmp(buff, str) < 0; }
} // namespace F100Lib
#endif
