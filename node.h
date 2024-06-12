#include "container.h"
#include <map>

namespace Approach::Render {
 using std::string;

 template<NativeStream S = std::ostream>
 class Node : public Container<S> {
 public:
	explicit Node(const string &content) {
	 this->content = content;
	 this->SetRenderID();
	};

	Node() {
	 this->content = "";
	 this->SetRenderID();
	};

	inline friend Node &operator<<(Node &to, Node &node) {
	 to.nodes.push_back(&node);
	 return to;
	}

	inline friend Node &operator<<(Node &to, Node *node) {
	 to.nodes.push_back(node);
	 return to;
	}
 };
}// namespace Approach::Render
