#include "xml.h"
#include <iostream>
#include <ostream>
using namespace std;

int main() {
  XML<ostream> div("div");
  XML<ostream> p("p");

  div << p;

  div >> cout;

  return 0;
}
