#include <iostream>

// This basically means anything that we can stream to
// I mean, for now, it's just going to check for a << operator
// but, eventually, the whole of the Streamability trait will be
// integrated and checked.
template <typename T>
concept Stream = requires(T t) {
  { t << nullptr } -> std::convertible_to<T &>;
};
