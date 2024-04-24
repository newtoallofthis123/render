#include "stream.h"

typedef unsigned long long int ProcUnit;

// The container class
template <Streamable streamT> class Container: Stream<streamT> {
};
