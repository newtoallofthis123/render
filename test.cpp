#include "streamtype.h"
#include "xml.h"
#include <vector>

int main() {
    StreamType<std::vector<char>, int, double, char, XML> stream1;
    return 0;
}
