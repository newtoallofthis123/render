#include "container.h"
#include <vector>

typedef unsigned long long int ProcUnit;

template <Streamability stream> class Node : public Container<stream> {
public:
  bool prerender;
  Node() : prerender(false) {}
  Node(bool _prerender) : prerender(_prerender) {}

  std::vector<Node *> nodes;

  inline void operator<<(Node *n) { this->nodes.push_back(n); }
  inline void operator<<(Node &n) { this->nodes.push_back(&n); }

  inline void operator>>(stream &s) { this->render(s); }

  inline Node operator[](unsigned int i) const {
    if (i >= this->nodes.size()) {
      throw std::out_of_range("Index out of range");
    }
    return *this->nodes[i];
  }
  inline Node &operator[](unsigned int i) {
    if (i >= this->nodes.size()) {
      throw std::out_of_range("Index out of range");
    }
    return *this->nodes[i];
  }

  void RenderHead(stream &s) {}
  void RenderCorpus(stream &s) {
    for (auto &n : this->nodes) {
      n->render(s);
    }
  }
  void RenderTail(stream &s) {}
};
