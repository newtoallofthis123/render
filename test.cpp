#include "xml.h"
#include <iostream>
#include <ostream>
using namespace std;

int main() {
  XML<ostream> div("div"), p("p"), h1("h1");

  p.content = "Hello, World!";
  h1.content = "Wow! You can really dance!";
  div << p;
  div << h1;

  auto some = div[1];
  some.render(cout);

  return 0;
}
