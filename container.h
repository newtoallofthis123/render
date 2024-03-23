#include "stream.h"
#include <vector>

typedef unsigned long long int ProcUnit;

// The container class
template <Streamable streamT> class Container {
public:
  std::vector<Container<streamT>> nodes;

  virtual void render(streamT &stream) {
    this->RenderHead(stream);
    this->RenderCorpus(stream);
    this->RenderTail(stream);
  }

  virtual void prerender(streamT &stream) {
    this->RenderHead(stream);
    this->RenderTail(stream);
  }

  virtual void RenderHead(streamT &stream) {}

  virtual void RenderCorpus(streamT &stream) {}

  virtual void RenderTail(streamT &stream) {}

  virtual void operator>>(streamT &stream) { this->render(stream); }

  virtual void operator<<(Container<streamT> *n) {
    this->nodes.push_back(*n);
  }
};
