#include <iostream>
#include "Graph.hpp"
#include "parser.hpp"
#include "algorithms.hpp"
#include "saver.hpp"
#include "checker.hpp"
#include "PLFlows.hpp"
#include "benchmarks.hpp"
#include <fstream>
using namespace std;

int main()
{
  // ligne suivante pour débugger prepush
  //   maxFlowComparison("../data/maxflow/instance_10_20_39.max", "instance_10_20_39.max", true);

  doAllBenchmarks();
  return 0;
}
