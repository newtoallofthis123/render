#include <algorithm>
#include <iostream>
#include <ostream>
#include <string>
#include <type_traits>
#include <vector>

template <typename T>
concept Streamability = requires(T t) {
  { t << "" };
};

template <typename T>
concept Store = requires(T t) {
  { t.begin() } -> std::same_as<typename T::iterator>;
  { t.end() } -> std::same_as<typename T::iterator>;
  { t.size() } -> std::integral;
};

template <typename StreamableType,
          template <typename...> typename ContainerType, typename... Args>
concept Keyspace = requires(StreamableType st) {
  { st.nodes } -> std::same_as<ContainerType<Args...>>;
};

template <typename StreamableType>
concept Streamable = std::is_base_of<std::ostream, StreamableType>::value;

typedef unsigned long long int ProcUnit;

template <Streamable streamT> class Stream {
public:
  std::string content;
  std::vector<Stream *> nodes;
  std::vector<std::string> _node_labels;
  std::vector<int> _labeled_nodes;

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

  Stream offsetGet(std::string label) {
    auto index = getNodeLabelIndex(label);
    return getLabeledNode(index);
  }

  void offsetSet(std::string label, Stream *obj) {
    auto offset = getNodeLabelIndex(label);

    if (offset == -1) {
      _labeled_nodes[nodes.size()] = nodes.size();
      // FIXME: Does'nt work:
      // The static casting fails for some reason
      // The error seems to be that the obj, which is being passed in as a XML
      // is unable to be casted as a Stream *
      nodes.push_back(static_cast<Stream *>(obj));
    } else {
    }
  }

  Stream getLabeledNode(int label_index) {
    return nodes[_labeled_nodes[label_index]];
  }

  int getNodeLabelIndex(std::string label) {
    auto offset = std::find(_node_labels.begin(), _node_labels.end(), label);
    if (offset != _node_labels.end()) {
      return offset - _node_labels.begin();
    } else {
      return -1;
    }
  }
};

// For now
// template <typename StreamableType,
//           template <typename...> typename ContainerType, typename LastArg,
//           typename... Args>
// concept LastParameterIsStream =
//     Keyspace<StreamableType, ContainerType, Args...> && Streamable<LastArg>;
