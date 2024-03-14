#include "xml.h"
#include <iostream>
#include <ostream>
using namespace std;

int main() {
  XML<ostream> div("div", "wow");
  XML<ostream> p("p");

  p.content = "Hello, World!";
  p.classes.push_back("wow");

  div << p;

  div >> cout;

  return 0;
}
