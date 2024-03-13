#include <ostream>
#include <type_traits>
#include <vector>

template <typename Streamable> class Container {
public:
  Streamable &stream;
  Container(Streamable &s) : stream(s) {}

  // vector type of anything that has the base class of Container
  std::vector<Container<Streamable> *> containers;

  virtual void render(Streamable &stream);

  virtual void RenderHead(Streamable &stream);
  virtual void RenderCorpus(Streamable &stream){

  }
  virtual void RenderTail(Streamable &stream);

  virtual void operator<<(Container<Streamable> &container);
  virtual void operator<<(Streamable &content);
};

template <typename T> struct is_container {
  static constexpr bool value =
      std::is_base_of<Container<std::ostream>, T>::value ||
      std::is_base_of<Container<T>, T>::value;
};
