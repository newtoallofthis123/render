#include "container.h"
#include <type_traits>

typedef unsigned long long int ProcUnit;

template <Stream stream> class Node : public Container<stream> {
public:
  // Static assert to check if ContainerType is derived from Container
  // static_assert(is_container<ContainerType>::value,
  //               "ContainerType must be derived from Container");

  std::string content;
  bool prerender;
  Node(stream &s) : Container<stream>(s), content(""), prerender(false) {}
  Node(stream &s, std::string c)
      : Container<stream>(s), content(c), prerender(false) {}
  Node(stream &s, std::string c, bool p)
      : Container<stream>(s), content(c), prerender(p) {}

  template <typename T>
  typename std::enable_if<is_container<T>::value, void>::type
  operator<<(Node<T> &node) {
    this->nodes.push_back(&node);
  }

  template <typename T>
  typename std::enable_if<!is_container<T>::value, void>::type
  operator<<(T &content) {
    this->content += content;
  }

  template <typename T>
  typename std::enable_if<is_container<T>::value, void>::type
  operator<<(T *node) {
    this->nodes.push_back(node);
  }

  template <typename T>
  typename std::enable_if<!is_container<T>::value, void>::type
  operator<<(T *content) {
    this->content += *content;
  }

  template <typename T, typename... Others> void add(T &content) {
    this->operator<<(content);
  }

  template <typename T, typename... Others>
  void add(T &content, Others &...others) {
    this->operator<<(content);
    this->add(others...);
  }
};
