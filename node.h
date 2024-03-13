#include "container.h"
#include <type_traits>
#include <vector>

typedef unsigned long long int ProcUnit;

template <typename ContainerType> class Node : public Container<ContainerType> {
public:
  // Static assert to check if ContainerType is derived from Container
  static_assert(is_container<ContainerType>::value,
                "ContainerType must be derived from Container");

  std::vector<Node *> nodes;
  std::string content;
  bool prerender;
  Node(ContainerType &s) : Container<ContainerType>(s) {}

  template <typename T>
  typename std::enable_if<is_container<T>::value, void>::type
  operator<<(Node<T> &node) {
    nodes.push_back(&node);
  }

  template <typename T>
  typename std::enable_if<!is_container<T>::value, void>::type
  operator<<(T &content) {
    this->content += content;
  }

  template <typename T>
  typename std::enable_if<is_container<T>::value, void>::type
  operator<<(T *node) {
    nodes.push_back(node);
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
