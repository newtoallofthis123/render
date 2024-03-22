#include "stream.h"
#include <vector>

typedef unsigned long long int ProcUnit;

// The container class
template <Stream StreamableType> class Container {
public:
  std::vector<Container<StreamableType>> nodes;

  virtual void render(StreamableType &stream) {
    this->RenderHead(stream);
    this->RenderCorpus(stream);
    this->RenderTail(stream);
  }

  virtual void prerender(StreamableType &stream) {
    this->RenderHead(stream);
    this->RenderTail(stream);
  }

  virtual void RenderHead(StreamableType &stream) {}

  virtual void RenderCorpus(StreamableType &stream) {}

  virtual void RenderTail(StreamableType &stream) {}

  virtual void operator>>(StreamableType &stream) { this->render(stream); }

  virtual void operator<<(Container<StreamableType> *n) {
    this->nodes.push_back(*n);
  }
};
