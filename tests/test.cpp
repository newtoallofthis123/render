//
// Created by noobscience on 6/12/24.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../render.h"

using namespace Approach::Render;

TEST_SUITE("Stream") {
		TEST_CASE("stream is an abstract class") {
		 CHECK(std::is_abstract<Stream<>>::value);
		}

		TEST_CASE("std::ostream can be NativeStream") {
		 CHECK(NativeStream<std::ostream>);
		}

		TEST_CASE("Stream's default type works") {
		 CHECK(std::is_base_of_v<Stream<>, Stream<>>);
		}
}

TEST_SUITE("Container") {
		TEST_CASE("Container is a subclass of Stream") {
		 CHECK(std::is_base_of_v<Stream<>, Container<>>);
		}

		TEST_CASE("Content works"){
		 Container<std::ostream> c;
		 c.content = "Hello, World!";

		 CHECK_EQ(c.content, "Hello, World!");
		}
}