#include "node.h"
#include <iostream>
#include <ostream>
using namespace std;

int main() {
  Node<ostream> n("Hello, World!");
  Node<ostream> n2("Cool, World!");
  
  n << &n2;

  n >> cout;

  return 0;
}
