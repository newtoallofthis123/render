#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "stream.h"
#include <sstream>
#include <vector>

class InheritedClass : public Stream {
public:
  std::vector<InheritedClass *> nodes;

  void render(std::stringstream &str) {
    this->RenderHead(str);
    this->RenderCorpus(str);
    this->RenderTail(str);
  }

  void RenderHead(std::stringstream &str) { str << "head "; }

  void RenderTail(std::stringstream &str) { str << "tail "; }

  void RenderCorpus(std::stringstream &str) {
    if (!this->nodes.empty())
      for (ProcUnit i = 0, L = this->nodes.size(); i < L; ++i) {
        str << *static_cast<InheritedClass *>(this->nodes[i]);
      }
  }

  inline friend std::stringstream &operator<<(std::stringstream &outputstream,
                                              InheritedClass &obj) {
    obj.render(outputstream);
    return outputstream;
  }
};

TEST_CASE("testing an inherited stream class's render") {
  InheritedClass i;

  std::stringstream str;

  i.render(str);

  auto expected = "head tail ";
  auto actual = str.str();

  CHECK(expected == actual);
}
