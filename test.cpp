#include "streamtype.h"
#include "xml.h"
#include <iostream>

using namespace std;
int main() {
  // Container c;
  // Container c1;
  // c1.content = "c1";
  // Container c2;
  // c2.content = "c2";
  //
  // c.offsetSet("hi", &c2);
  // c.offsetSet("hello", &c1);
  //
  // for (auto i : c._node_labels) {
  //   cout << i;
  // }
  // cout << endl;
  // for (auto i : c._labeled_nodes) {
  //   cout << i;
  // }

  // cout << c.offsetGet("hi")->content << endl;
  // cout << c.offsetGet("hello")->content;

  XML p("p");
  
  cout << p;

  return 0;
}
