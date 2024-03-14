#include <iostream>
#include <ostream>
#include "node.h"
using namespace std;

int main() {
  typedef Container<ostream> ostream_container;

  Container<ostream> c(cout);
  // Node<ostream_container> node(c);
  // Node<ostream_container> n2(c);
  // Node<ostream_container> n3(c);
  //
  // string s = "Hello";
  // string s2 = "World";
  //
  // node.add(s, n2, s2, n3);
  //
  // cout << node.content << endl;

  return 0;
}
