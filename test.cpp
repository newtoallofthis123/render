#include "xml.h"
#include <iostream>

int main() {
  // StreamType<std::vector<int>, int, double, char, XML> stream1;

  XML p("p");
  p.content = "Hello World";

  std::cout << p;

  return 0;
}
