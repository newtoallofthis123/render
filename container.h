#include "stream.h"
#include <ostream>

// The container class
class Container : public Stream<std::ostream> {};
