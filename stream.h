#include <iostream>

// This basically means anything that we can stream to
// I mean, for now, it's just going to check for a << operator
// but, eventually, the whole of the Streamability trait will be
// integrated and checked.
// WARNING: To be DEPPRECATED soon
template <typename T>
concept Stream = requires(T t) {
  { t << std::declval<const char *>() }; // Supports streaming const char*
};

template <typename T>
concept Store = requires(T t) {
  { t.begin() } -> std::same_as<typename T::iterator>;
  { t.end() } -> std::same_as<typename T::iterator>;
  { t.size() } -> std::integral;
};

template <typename T>
concept HasPushBack =
    requires(T t) { t.push_back(std::declval<typename T::value_type>()); };

template <typename T>
concept HasInsert =
    requires(T t) { t.insert(std::declval<typename T::value_type>()); };

template <Store store, typename... Args> class StreamUtil {
public:
  StreamUtil(store &s) : s(s) {}
  store s;

  void add(Args... args) {
    if constexpr (HasPushBack<store>) {
      (s.push_back(args), ...);
    } else if constexpr (HasInsert<store>) {
      (s.insert(args), ...);
    } else {
      std::cout << "No push_back or insert found" << std::endl;
    }
  }

  void print() {
    if constexpr (HasPushBack<store>) {
      for (auto &i : s) {
        std::cout << i << " ";
      }
    } else if constexpr (HasInsert<store>) {
      for (auto &i : s) {
        std::cout << i.first << " " << i.second << " ";
      }
    } else {
      std::cout << "No push_back or insert found" << std::endl;
    }
  }
};
