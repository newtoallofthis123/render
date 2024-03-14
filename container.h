#include "stream.h"
#include <vector>

// The container class
template <Stream StreamableType> class Container {
public:
  StreamableType &stream;

  Container(StreamableType &s) : stream(s) {}

  virtual ~Container() = default;

  typedef unsigned long long int ProcUnit;
  std::vector<Container *> nodes;

  virtual void render(StreamableType &stream) {
    this->RenderHead(stream);
    this->RenderCorpus(stream);
    this->RenderTail(stream);
  }

  virtual void RenderHead(StreamableType &stream) {}

  virtual void RenderCorpus(StreamableType &stream) {
    if (!this->nodes.empty()) {
      for (ProcUnit i = 0, L = this->nodes.size(); i < L; ++i) {
        // stream << *this->nodes[i];
        // This is going to be where the actual stuff gets appended to the
        // stream.
        // Now this is where I would need to figure out how to actually
      }
    }
  }

  virtual void RenderTail(StreamableType &stream) {}

  virtual void operator>>(StreamableType &stream) { this->render(stream); }
};

// Check if a type is a container
template <typename T> struct is_container {
  static constexpr bool value = std::is_base_of<Container<std::ostream>, T>::value ||
                                std::is_base_of<Container<T>, T>::value;
};
