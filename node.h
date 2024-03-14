#include "container.h"

typedef unsigned long long int ProcUnit;

template <Stream stream> class Node : public Container<stream> {
public:
  // Static assert to check if ContainerType is derived from Container
  // static_assert(is_container<Node>::value,
  // "ContainerType must be derived from Container");

  std::string content;
  bool prerender;
  Node(stream &s) : Container<stream>(s), content(""), prerender(false) {}
  Node(stream &s, std::string c)
      : Container<stream>(s), content(c), prerender(false) {}
  Node(stream &s, std::string c, bool p)
      : Container<stream>(s), content(c), prerender(p) {}

  inline void operator<<(Node *n) { this->nodes.push_back(n); }
  inline void operator<<(Node &n) { this->nodes.push_back(&n); }
  inline void operator>>(stream &s) { this->render(s); }

  void RenderHead(stream &s){
    s << this->content;
  }
};
