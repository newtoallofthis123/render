#include "streamtype.h"
#include "xml.h"
#include <iostream>

class SomeClass {
public:
  Stream stream;
};

int main() {
  SomeClass h;
  Stream instanceOfStream;
  h.stream.hello(instanceOfStream);

  return 0;
}
