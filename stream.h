#include <iostream>
#include <ostream>
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

template<Streamable streamT>
class Stream {
public:
  std::vector<Stream<streamT>> nodes;

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
};

// For now
// template <typename StreamableType,
//           template <typename...> typename ContainerType, typename LastArg,
//           typename... Args>
// concept LastParameterIsStream =
//     Keyspace<StreamableType, ContainerType, Args...> && Streamable<LastArg>;
