#include "xml.h"
#include <iostream>
#include <ostream>
using namespace std;

int main() {
  XML<std::ostream> div("div");

  XML<std::ostream> h1("h1");
  h1.content = "Hello World!";

  div << h1;

  cout << div;
}
