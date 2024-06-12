#include <concepts>
#include <ios>
#include <iostream>
#include <ostream>
#include <type_traits>

template<typename T>
concept Store = requires(T t) {
 { t.begin() } -> std::same_as<typename T::iterator>;
 { t.end() } -> std::same_as<typename T::iterator>;
 { t.size() } -> std::integral;
};

template<typename T>
concept NativeStream = std::is_base_of_v<
				std::basic_ios<typename T::char_type, typename T::traits_type>,
				std::remove_pointer_t<T>>;

typedef unsigned long long int ProcUnit;

namespace Approach::Render {
		template<NativeStream S = std::ostream>
		class Stream {
		public:
				virtual void render(S &stream) = 0;

				virtual void RenderHead(S &stream) = 0;

				virtual void RenderCorpus(S &stream) = 0;

				virtual void RenderTail(S &stream) = 0;
		};
} // namespace Approach::Render
