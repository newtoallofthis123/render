#include "container.h"

typedef unsigned long long int ProcUnit;

template <Streamability stream> class Node : public Container<stream> {
};
