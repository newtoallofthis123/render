#include "xml.h"
#include <iostream>
#include <ostream>
#include <sstream>
using namespace std;

int main() {
  XML<std::stringstream> div("div"), p("p"), h1("h1");

  div.content = "wow";
  p.content = "hello";
  h1.content = "world";

  div << p;
  div << h1;

  auto output = std::stringstream();

  output << div;

  cout << output.str() << endl;

  return 0;
}
