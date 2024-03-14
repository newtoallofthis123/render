#include "node.h"
#include <iostream>
#include <ostream>
using namespace std;

int main() {
  Node<ostream> node(cout, "Hello");
  // Node<ostream> n2(cout);
  // Node<ostream> n3(cout);

  string s = "Hello";
  string s2 = "World";

  // node.add(s, n2, s2, n3);

  cout << node.content << endl;

  return 0;
}
