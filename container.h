#include "stream.h"
#include <vector>

// The container class
template <Stream StreamableType> class Container {
public:
  typedef unsigned long long int ProcUnit;
  std::vector<Container<StreamableType>> nodes;

  virtual void render(StreamableType &stream) {
    this->RenderHead(stream);
    this->RenderCorpus(stream);
    this->RenderTail(stream);
  }

  virtual void RenderHead(StreamableType &stream) {}

  virtual void RenderCorpus(StreamableType &stream) {}

  virtual void RenderTail(StreamableType &stream) {}

  virtual void operator>>(StreamableType &stream) { this->render(stream); }
};

// Check if a type is a container
template <typename T> struct is_container {
  static constexpr bool value =
      std::is_base_of<Container<std::ostream>, T>::value ||
      std::is_base_of<Container<T>, T>::value;
};
