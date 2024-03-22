#include "stream.h"
#include <map>
#include <set>
#include <vector>
using namespace std;

int main() {
  vector<int> v;
  StreamUtil<vector<int>, int, int, int, int, int> su(v);

  su.add(1, 2, 3, 4, 5);
  su.print();

  // map<int, string> m;
  // StreamUtil<map<int, string>, pair<int, string>, pair<int, string>> su2(m);
  //
  // su2.add(make_pair(1, "one"), make_pair(2, "two"));
  // su2.print();
  //
  set<int> s;
  StreamUtil<set<int>, int, int, int> su3(s);

  su3.add(1, 2, 3);
  su3.print();
}
