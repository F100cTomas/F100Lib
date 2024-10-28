#include <iostream>
#include <F100Lib.hpp>

using namespace F100Lib;

static std::ostream& operator<<(std::ostream& stream, SizedStringRef s) {
  for (char c: s) stream << c;
  return stream;
}

int main() {
}
