#include <ostream>
#include <type_traits>
#include <vector>

template <typename Streamable> class Container {
public:
  Streamable &stream;
  Container(Streamable &s) : stream(s) {}
  virtual ~Container() = default;

  typedef unsigned long long int ProcUnit;
  std::vector<Container *> nodes;

  // virtual void render(Streamable &stream);
  //
  // virtual void RenderHead(Streamable &stream);
  virtual void RenderCorpus(Streamable &stream) {
    if (!this->nodes.empty()) {
      for (ProcUnit i = 0, L = this->nodes.size(); i < L; ++i) {
        // stream << *this->nodes[i];
      }
    }
  }
  // virtual void RenderTail(Streamable &stream);
  //
  // virtual void operator<<(Container<Streamable> &container);
  // virtual void operator<<(Streamable &content);
};

template <typename T> struct is_container {
  static constexpr bool value =
      std::is_base_of<Container<std::ostream>, T>::value ||
      std::is_base_of<Container<T>, T>::value;
};
