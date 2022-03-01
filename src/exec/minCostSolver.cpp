#include <iostream>
#include "Graph.hpp"
#include "parser.hpp"
#include "PLFlows.hpp"

using namespace std;

int main(int argc, char *const argv[])
{
    Graph graph = minCost::parse(argv[1], false);
    PL::minCost(graph, true);
}