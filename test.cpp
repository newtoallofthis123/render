#include "streamtype.h"
#include "xml.h"
#include <vector>

int main() {
    StreamType<std::vector<int>, double, char, Node> stream1;
}
