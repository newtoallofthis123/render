#include <iostream>
#include <ostream>
#include <type_traits>

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

// template <typename StreamableType,
//           template <typename...> typename ContainerType, typename... Args>
// concept Keyspace = requires(StreamableType st) {
//   { st.nodes } -> std::same_as<ContainerType<Args...>>;
// };


template <typename StreamableType>
concept Streamable = std::is_base_of<std::ostream, StreamableType>::value;

typedef unsigned long long int ProcUnit;

template <Streamable streamT> class Stream {
public:
  virtual void render(streamT &stream) = 0;

  virtual void prerender(streamT &stream) = 0;

  virtual void RenderHead(streamT &stream) = 0;

  virtual void RenderCorpus(streamT &stream) = 0;

  virtual void RenderTail(streamT &stream) = 0;
};

// For now
// template <typename StreamableType,
//           template <typename...> typename ContainerType, typename LastArg,
//           typename... Args>
// concept LastParameterIsStream =
//     Keyspace<StreamableType, ContainerType, Args...> && Streamable<LastArg>;
