#include "node.h"
#include <iostream>
#include <ostream>
using namespace std;

int main() {
  auto node = Node<ostream>(cout, "Hello");
  auto n2 = Node<ostream>(cout, "World");
  auto n3 = Node<ostream>(cout, "!!!");

  node << &n2;
  node << n3;

  node >> cout;

  return 0;
}
