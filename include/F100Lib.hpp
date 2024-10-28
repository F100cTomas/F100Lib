#ifndef F100LIB_HPP
#define F100LIB_HPP
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <type_traits>
namespace F100Lib {
// Class declaration
template <typename T, size_t size> class Array;
template <typename T> class Vector;
class StringRef;
class SizedStringRef;
template <size_t size> class StackString;
class HeapString;
// Function declaration
constexpr size_t strlen(const char* str);
// Class definition
template <typename T, size_t size> class Array {
  T buff[size];
};
template <typename T> class Vector {
  T*     buff     = nullptr;
  size_t buffSize = 0;
  size_t capacity = 0;
public:
  constexpr Vector();
  constexpr Vector(const Vector<T>& v);
  constexpr Vector(Vector<T>&& v);
  inline ~Vector();
  inline Vector<T>& operator=(const Vector<T>& str);
  inline Vector<T>& operator=(Vector<T>&& str);
public:
  constexpr T*       begin();
  constexpr T*       end();
  constexpr const T* begin() const;
  constexpr const T* end() const;
  inline T&          operator[](size_t i);
  inline const T&    operator[](size_t i) const;
  constexpr size_t   size() const;
public:
  inline void expand();
  inline void resize(size_t newSize);
  inline void free();
};
class StringRef {
  char* buff;
public:
  constexpr StringRef(char* str);
  constexpr StringRef(const char* str);
  constexpr StringRef(const StringRef& str);
  inline ~StringRef();
  inline StringRef& operator=(const StringRef& str);
  inline StringRef& operator=(StringRef&&) = delete;
  inline void       free();
public:
  constexpr             operator char*();
  constexpr             operator const char*() const;
  inline SizedStringRef of_size(size_t s);
public:
  constexpr size_t      length() const;
  constexpr const char* get() const;
public:
  constexpr char*       begin();
  constexpr char*       end();
  constexpr const char* begin() const;
  constexpr const char* end() const;
public:
  inline char&       operator[](size_t i);
  inline const char& operator[](size_t i) const;
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
  inline SizedStringRef& operator=(const SizedStringRef& str);
  inline SizedStringRef& operator=(SizedStringRef&&) = delete;
  inline void            free();
public:
  constexpr operator char*();
  constexpr operator const char*() const;
public:
  constexpr size_t      length() const;
  constexpr size_t      size() const;
  constexpr const char* get() const;
public:
  constexpr char*       begin();
  constexpr char*       end();
  constexpr const char* begin() const;
  constexpr const char* end() const;
  static inline void    operator delete(void* ptr);
public:
  inline char&                                operator[](size_t i);
  inline const char&                          operator[](size_t i) const;
  void                                        operator+=(const char c);
  void                                        operator+=(const StringRef str);
  void                                        operator+=(int32_t i);
  void                                        operator+=(int64_t i);
  template <typename T> inline SizedStringRef operator<<(const T& t);
public:
  inline bool operator==(const StringRef str) const;
  inline bool operator!=(const StringRef str) const;
  inline bool operator>=(const StringRef str) const;
  inline bool operator<=(const StringRef str) const;
  inline bool operator>(const StringRef str) const;
  inline bool operator<(const StringRef str) const;
};
template <size_t size> class StackString {
  Array<char, size> buff;
};
class HeapString {
  Vector<char> buff;
};
// Function definition
constexpr size_t strlen(const char* str) { return (*str) ? 1 + strlen(str + 1) : 0; }
// Method definition
template <typename T> constexpr Vector<T>::Vector() {}
template <typename T>
constexpr Vector<T>::Vector(const Vector<T>& v) : buff(reinterpret_cast<T*>(malloc(sizeof(T) * v.buffSize))), buffSize(v.buffSize), capacity(v.buffSize) {
  for (size_t i = 0; i < buffSize; i++) new (buff + i) T(v.buff[i]);
}
template <typename T> constexpr Vector<T>::Vector(Vector<T>&& v) : buff(v.buff), buffSize(v.buffSize), capacity(v.capacity) {
  v.buff     = nullptr;
  v.buffSize = 0;
  v.capacity = 0;
}
template <typename T> inline Vector<T>::~Vector() { free(); }
template <typename T> inline Vector<T>& Vector<T>::operator=(const Vector<T>& v) {
  if (this == &v) return *this;
  for (size_t i = 0; i < buffSize; i++) buff[i].~T();
  if (v.buffSize > capacity)
    resize(v.buffSize);
  else
    buffSize = v.buffSize;
  for (size_t i = 0; i < buffSize; i++) new (buff + i) T(v.buff[i]);
  return *this;
}
template <typename T> inline Vector<T>& Vector<T>::operator=(Vector<T>&& v) {
  free();
  buff       = v.buff;
  buffSize   = v.buffSize;
  capacity   = v.capacity;
  v.buff     = nullptr;
  v.buffSize = 0;
  v.capacity = 0;
  return *this;
}
template <typename T> constexpr T*       Vector<T>::begin() { return buff; }
template <typename T> constexpr T*       Vector<T>::end() { return buff + buffSize; }
template <typename T> constexpr const T* Vector<T>::begin() const { return buff; }
template <typename T> constexpr const T* Vector<T>::end() const { return buff + buffSize; }
template <typename T> inline T&          Vector<T>::operator[](size_t i) {
  if (i >= buffSize) resize(i + 1);
  return buff[i];
}
template <typename T> inline const T&  Vector<T>::operator[](size_t i) const { return buff[i]; }
template <typename T> constexpr size_t Vector<T>::size() const { return buffSize; }
template <typename T> inline void      Vector<T>::expand() {
  capacity = capacity == 0 ? 1 : capacity * 2;
  buff     = reinterpret_cast<T*>(realloc(buff, sizeof(T) * capacity));
}
template <typename T> inline void Vector<T>::resize(size_t newSize) {
  buff     = reinterpret_cast<T*>(realloc(buff, sizeof(T) * newSize));
  buffSize = newSize;
  capacity = newSize;
}
template <typename T> inline void Vector<T>::free() {
  if (buff == nullptr) return;
  if constexpr (!std::is_trivially_destructible<T>::value)
    for (size_t i = 0; i < buffSize; i++) buff[i].~T();
  free(buff);
}
constexpr StringRef::StringRef(char* str) : buff(str) {}
constexpr StringRef::StringRef(const char* str) : buff(const_cast<char*>(str)) {}
constexpr StringRef::StringRef(const StringRef& str) : buff(str.buff) {}
inline StringRef::~StringRef() {}
inline StringRef& StringRef::operator=(const StringRef& str) {
  buff = str.buff;
  return *this;
}
inline void StringRef::free() { delete[] buff; }
constexpr StringRef::operator char*() { return buff; }
constexpr StringRef::operator const char*() const { return buff; }
inline SizedStringRef StringRef::of_size(size_t s) { return SizedStringRef(buff, s); }
constexpr size_t      StringRef::length() const { return strlen(buff); }
constexpr const char* StringRef::get() const { return buff; }
constexpr char*       StringRef::begin() { return buff; }
constexpr char*       StringRef::end() { return buff + length(); }
constexpr const char* StringRef::begin() const { return buff; }
constexpr const char* StringRef::end() const { return buff + length(); }
inline char&          StringRef::operator[](size_t i) { return buff[i]; }
inline const char&    StringRef::operator[](size_t i) const { return buff[i]; }
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
inline SizedStringRef& SizedStringRef::operator=(const SizedStringRef& str) {
  buff     = str.buff;
  buffSize = str.buffSize;
  return *this;
}
inline void SizedStringRef::free() { delete[] buff; }
constexpr SizedStringRef::operator char*() { return buff; }
constexpr SizedStringRef::operator const char*() const { return buff; }
constexpr size_t                            SizedStringRef::length() const { return strlen(buff); }
constexpr size_t                            SizedStringRef::size() const { return buffSize; }
constexpr const char*                       SizedStringRef::get() const { return buff; }
constexpr char*                             SizedStringRef::begin() { return buff; }
constexpr char*                             SizedStringRef::end() { return buff + length(); }
constexpr const char*                       SizedStringRef::begin() const { return buff; }
constexpr const char*                       SizedStringRef::end() const { return buff + length(); }
inline char&                                SizedStringRef::operator[](size_t i) { return buff[i]; }
inline const char&                          SizedStringRef::operator[](size_t i) const { return buff[i]; }
template <typename T> inline SizedStringRef SizedStringRef::operator<<(const T& t) {
  (*this) += t;
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
