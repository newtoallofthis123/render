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

// check if the store is a vector
template <typename T>
concept Vector = Store<T> && requires(T t) {
  { t.push_back(std::declval<typename T::value_type>()) };
};

// check if the store is a map, i.e., it has insert and also has a key_type
template <typename T>
concept Map = Store<T> && requires(T t) {
  { t.insert(std::declval<typename T::value_type>()) };
  { t.key_type } -> std::same_as<typename T::key_type>;
};

// check if the store is a set
template <typename T>
concept Set = Store<T> && requires(T t) {
  { t.insert(std::declval<typename T::value_type>()) };
};

template <Store store, typename... Args> class StreamUtil {
public:
  StreamUtil(store &s) : s(s) {}
  store s;

  void add(Args... args) {
    if constexpr (Vector<store>) {
      (s.push_back(args), ...);
    } else if constexpr (Map<store>) {
      (s.insert(args), ...);
    } else if constexpr (Set<store>) {
      (s.insert(args), ...);
    }
  }

  void print() {
    if constexpr (Vector<store> || Set<store>) {
      for (auto &i : s) {
        std::cout << i << " ";
      }
      std::cout << std::endl;
    } else if constexpr (Map<store>) {
      for (auto &i : s) {
        std::cout << i.first << " " << i.second << std::endl;
      }
    } else{
      std::cout << "Don't know how to print this store" << std::endl;
    }
  }
};
