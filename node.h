#include "container.h"
#include <vector>

typedef unsigned long long int ProcUnit;

template <Stream stream> class Node : public Container<stream> {
public:
  // Static assert to check if ContainerType is derived from Container
  // static_assert(is_container<Node>::value,
  // "ContainerType must be derived from Container");

  bool prerender;
  Node() : prerender(false) {}
  Node(bool _prerender) : prerender(_prerender) {}

  std::vector<Node *> nodes;

  inline void operator<<(Node *n) { this->nodes.push_back(n); }
  inline void operator<<(Node &n) { this->nodes.push_back(&n); }

  inline void operator>>(stream &s) { this->render(s); }

  void RenderHead(stream &s) {}
  void RenderCorpus(stream &s) {
    for (auto &n : this->nodes) {
      n->render(s);
    }
  }
  void RenderTail(stream &s) {}
};
