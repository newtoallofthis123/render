#include "keyspace.h"
#include <string>

int main() {
  std::vector<KeySpace<int, int, int, XML>> coordinates;
  coordinates.push_back(KeySpace<int, int, int, XML>(12, 13, 14, XML("div")));
  coordinates.push_back(KeySpace<int, int, int, XML>(-8, -1, -23, XML("a")));
  coordinates.push_back(KeySpace<int, int, int, XML>(-131, 121, 31, XML("p")));

  // std::vector<KeySpace<int, int, std::string>> nodes;
  // nodes.push_back(KeySpace<int, int, std::string>(12, 13, "Hello"));
  // nodes.push_back(KeySpace<int, int, std::string>(-8, -1, "Hi"));
  // nodes.push_back(KeySpace<int, int, std::string>(-131, 121, "Wow"));

  for (auto r : coordinates) {
    std::cout << std::endl;
    // r.print_values();
    r.keyspace_types();
  }
}
