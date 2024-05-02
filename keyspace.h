// WARNING: The Keyspace thing is wrong
//
// template <typename StreamableType,
//           template <typename...> typename ContainerType, typename... Args>
// class Keyspace {
//   ContainerType<Args...> nodes;
// };

#include <iostream>

template <typename... Args> class KeySpaceWrong {
public:
  std::tuple<Args...> types;

  template <std::size_t I = 0> void print_values() {
    if constexpr (I < sizeof...(Args)) {
      std::cout << std::get<I>(types) << std::endl;
      print_values<I + 1>();
    }
  }

  KeySpaceWrong(Args... args) : types(std::make_tuple(args...)) {}
};
