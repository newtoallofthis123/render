#include "xml.h"
#include <iostream>
using namespace std;

int main() {
  XML div("div");
  XML div1("div");

  XML h1("h1");
  h1.content = "Hello World!";
  h1.id = "hi";

  XML p("span");
  p.content = "Cool";
  p.id = "cool";

  h1 << p;
  div << h1;

  cout << div;
}
