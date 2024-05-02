#include <iostream>

template <typename T>
concept ContainerType = requires(T t) {
  { t.begin() } -> std::same_as<typename T::iterator>;
  { t.end() } -> std::same_as<typename T::iterator>;
  { t.size() } -> std::integral;
};

template <typename T>
concept StreamConcept = requires(T t) {
  { t.render() } -> std::same_as<void>;
  { t.RenderHead() } -> std::same_as<void>;
  { t.RenderCorpus() } -> std::same_as<void>;
  { t.RenderTail() } -> std::same_as<void>;
};

template <typename T> struct IsStreamable {
  static constexpr bool value = StreamConcept<T>;
};

// NOTE: All this was replaced by the Concept
//
// template <typename T> void CheckStreamable() {
//   static_assert(IsStreamable<T>::value,
//                 "Last type in Keyspace must be Streamable");
// }
//
// template <typename T, typename... Args> void CheckStreamable() {
//   CheckStreamable<Args...>();
// }

template <ContainerType ct, typename... Keyspace> class StreamType {
  static_assert(sizeof...(Keyspace) > 0,
                "At least one type in Keyspace is required");
  static_assert(
      IsStreamable<typename std::tuple_element<
          sizeof...(Keyspace) - 1, std::tuple<Keyspace...>>::type>::value,
      "Last type in Keyspace must be Streamable");
};
