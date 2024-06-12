#include "stream.h"
#include <algorithm>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

namespace Approach::Render {
 template<NativeStream S = std::ostream>
 class Container : public Stream<S> {
 private:
	ProcUnit ActiveRenderCount = 0;

 public:
	ProcUnit RenderID{};
	std::vector<Stream<S> *> nodes;

	Container() { SetRenderID(); }

	std::vector<std::string> _node_labels;
	std::vector<size_t> _labeled_nodes;
	std::string content;

	// Set Unique Global Render ID based on static member ActiveRenderCount
	void SetRenderID() {
	 RenderID = ActiveRenderCount;
	 ++ActiveRenderCount;
	};

	Stream<S> *offsetGet(const std::string &label) {
	 auto index = getNodeLabelIndex(label);
	}

	void offsetSet(const std::string &label, Stream<S> *obj) {
	 auto offset = getNodeLabelIndex(label);

	 this->nodes.push_back(obj);
	 if (offset == -1) {
		_labeled_nodes.push_back(this->nodes.size() - 1);
		_node_labels.push_back(label);
	 } else {
		_labeled_nodes[offset] = this->nodes.size() - 1;
		_node_labels[offset] = label;
	 }
	}

	Stream<S> *getLabeledNode(int label_index) {
	 return this->nodes[_labeled_nodes[label_index]];
	}

	int getNodeLabelIndex(const std::string &label) {
	 auto offset = std::find(_node_labels.begin(), _node_labels.end(), label);
	 if (offset != _node_labels.end()) {
		return offset - _node_labels.begin();
	 } else {
		return -1;
	 }
	}

	void render(std::ostream &stream) override {
	 this->RenderHead(stream);
	 this->RenderCorpus(stream);
	 this->RenderTail(stream);
	}

	void RenderHead(std::ostream &stream) override {
	}

	void RenderCorpus(std::ostream &stream) override {
	 for (auto &node: this->nodes) {
		stream << node;
	 }
	}

	void RenderTail(std::ostream &stream) override {
	}

	void prerender(std::ostream &stream) {
	 this->RenderHead(stream);
	 this->RenderTail(stream);
	}

	Stream<S> *operator[](const std::string &label) { return offsetGet(label); }

	// enable s[0] = new Stream();
	Stream<S> *operator[](int index) { return nodes[index]; }

	// enable setting s[0] = new Stream();
	Container &operator=(Stream<S> *node) {
	 this->nodes.push_back(node);
	 return *this;
	}

	// add << operator to add a node to the container
	inline Container &operator<<(Stream<S> &node) {
	 this->nodes.push_back(&node);
	 return *this;
	}

	inline friend Container &operator<<(Stream<S> &node, Container &to) {
	 to.nodes.push_back(&node);
	 return to;
	}

	// add << operator to add a node to the container
	inline Container &operator<<(Stream<S> *node) {
	 this->nodes.push_back(node);
	 return *this;
	}

	inline friend Container &operator<<(Stream<S> *node, Container &to) {
	 to.nodes.push_back(node);
	 return to;
	}

	/** Supports "normal" syntax cout<<XML; is not really a member function */
	inline friend Stream<S> &operator<<(Container &to, Container &node) {
	 to.nodes.push_back(&node);
	 return to;
	}

	/* Typecast from XML to Node by calling XML.render() into Node.content */
	inline explicit operator std::string() {
	 std::ostringstream stream;
	 this->prerender(stream);
	 return stream.str();
	}

	// Make typecasts friendly
	inline friend Container &operator<<(Container &to, std::string &node) {
	 to.content += node;
	 return to;
	}

	inline friend Container &operator<<(Container &to, const char *node) {
	 to.content += node;
	 return to;
	}
 };
}// namespace Approach::Render

/*
  Add friend << operator to add a node to the container
*/
template<NativeStream S>
inline Approach::Render::Stream<S> &
operator<<(Approach::Render::Container<S> &container,
					 Approach::Render::Stream<S> &node) {
 container.nodes.push_back(&node);
 return node;
}

template<NativeStream S>
inline Approach::Render::Stream<S> &
operator<<(Approach::Render::Container<S> &container,
					 Approach::Render::Stream<S> *node) {
 container.nodes.push_back(node);
 return *node;
}