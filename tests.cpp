#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "xml.h"
#include <sstream>

TEST_CASE("Testing XML") {
  std::string expected = "\n<p>\nHello World\n\n</p>";

  XML xml("p");
  xml.content = "Hello World";
  

  std::ostringstream buffer;
  buffer << xml;

  SUBCASE("Renders to buffer"){
    CHECK(buffer.str().size() != 0);
  }

  SUBCASE("Check Rendered Similarity"){
    CHECK(buffer.str() == expected);
  }
}

TEST_CASE("Testing Stream"){
  Stream ss;

  SUBCASE("Stream exists"){
  }
}
