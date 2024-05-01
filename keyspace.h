// template <typename StreamableType,
//           template <typename...> typename ContainerType, typename... Args>
// class Keyspace {
//   ContainerType<Args...> nodes;
// };

#include "xml.h"
#include <iostream>

template <typename... Args> class KeySpace {
public:
  std::tuple<Args...> types;

  template <std::size_t I = 0> void print_values() {
    if constexpr (I < sizeof...(Args)) {
      std::cout << std::get<I>(types) << std::endl;
      print_values<I + 1>();
    }
  }

  KeySpace(Args... args) : types(std::make_tuple(args...)) {}
};
