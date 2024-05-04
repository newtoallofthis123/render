#define BOOST_TEST_MODULE STREAM_TEST
#include <sstream>
#include <vector>
#include "stream.h"
#include <boost/test/included/unit_test.hpp>

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

BOOST_AUTO_TEST_CASE(testing_stream) {
  InheritedClass i;

  std::stringstream str;

  i.render(str);

  auto expected = "head tail ";
  auto actual = str.str();
  std::cout << str.str();

  BOOST_CHECK(expected == actual);
}
