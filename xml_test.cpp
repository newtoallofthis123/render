#include <algorithm>
#include <sstream>
#define BOOST_TEST_MODULE XML_TEST

#include "xml.h"
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(testing_xml) {
  std::string expected = "<p>HelloWorld</p>";

  XML xml("p");
  xml.content = "HelloWorld";

  std::ostringstream buffer;
  buffer << xml;

  std::string actual = buffer.str();

  // Remove spaces for now :)
  actual.erase(std::remove(actual.begin(), actual.end(), '\n'), actual.end());
  actual.erase(std::remove(actual.begin(), actual.end(), ' '), actual.end());

  BOOST_CHECK(expected == actual);
}
