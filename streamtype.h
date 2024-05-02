#include <concepts>
#include <ostream>
#include <tuple>

// HACK: This should work for most common container types in cpp, like
// std::vector or std::tuple, however a more generalized container would
// be ideal
template <typename T>
concept ContainerType = requires(T t) {
  { t.begin() } -> std::same_as<typename T::iterator>;
  { t.end() } -> std::same_as<typename T::iterator>;
  { t.size() } -> std::integral;
};

// HACK: Make it such that it accepts any stream, not just ostream
// For now, turns out that the declval type has to work with a real type
// hence, it cannot be something abstract like something that can be streamed
// to. However, this should suffice for most Node based Render Classes
template <typename T>
concept Streamable = requires(T t) {
  { t.render(std::declval<std::ostream &>()) } -> std::same_as<void>;
  { t.RenderHead(std::declval<std::ostream &>()) } -> std::same_as<void>;
  { t.RenderCorpus(std::declval<std::ostream &>()) } -> std::same_as<void>;
  { t.RenderTail(std::declval<std::ostream &>()) } -> std::same_as<void>;

  // NOTE: These can be enabled once stream has been incorporated into the
  // Stream base class
  //
  // { t.stream(std::declval<std::ostream &>()) } -> std::same_as<void>;
  // { t.StreamHead(std::declval<std::ostream &>()) } -> std::same_as<void>;
  // { t.StreamCorpus(std::declval<std::ostream &>()) } -> std::same_as<void>;
  // { t.StreamTail(std::declval<std::ostream &>()) } -> std::same_as<void>;
};

template <ContainerType ct, typename... Keyspace> class StreamType {
  static_assert(sizeof...(Keyspace) > 0,
                "At least one type in Keyspace is required");
  static_assert(Streamable<typename std::tuple_element<
                    sizeof...(Keyspace) - 1, std::tuple<Keyspace...>>::type>,
                "Last type in Keyspace must be Streamable");
};
