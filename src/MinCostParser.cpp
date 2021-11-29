#include "Structures.hpp"
using namespace std;

// this function parse an input file and return a network graph
// parameters: filepath
// return value: graph
Graph parse(std::string filePath)
{
    // data format example:
    // "c 20 msec" comment line, to skip
    // "p min 49 520" problem line where the first number is the number of nodes and the second number is the number of edges
    // "n 47 -769230" nodes line, the first number is the node id, the second number is the node flow
    // "a 1 5 0 769230 1132" edge line, the first number is the source node id, the second number is the destination node id,
    // the third number is the minimum flow capacity, the fourth number is the maximum flow capacity,
    // the fifth number is the cost of the edge
}
