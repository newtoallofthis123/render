#include <iostream>
#include <type_traits>

template <typename T>
concept Streamability = requires(T t) {
  { t << std::declval<const char *>() };
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

class Stream {
public:
  virtual void operator<<(const char *s) = 0;
};

template <typename StreamableType>
concept Streamable = std::is_base_of<Stream, StreamableType>::value;

template <typename StreamableType,
          template <typename...> typename ContainerType, typename LastArg,
          typename... Args>
concept LastParameterIsStream =
    Keyspace<StreamableType, ContainerType, Args...> && Streamable<LastArg>;
