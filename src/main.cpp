#include <iostream>
#include "Graph.hpp"
#include "parser.hpp"
#include "algorithm.hpp"
#include "saver.hpp"
#include "checker.hpp"
#include "PLFlows.hpp"
#include "PreflowPush.hpp"
#include "benchmarks.hpp"
using namespace std;

int main()
{
  maxFlowComparison("../data/maxflow/maxFlowTest500v5000e.max",true);
  //maxFlowBenchmarks(true);

  //graph.print();
  //cout << endl;
  //cout << "Residual graph:\n";
  //cout << endl;
  //Graph graphMax = maxflow::parse("../data/maxflow/instance_1.max");
  //PL::maxFlow(graphMax);

  // graph.removeLonelyNodes();
  // Graph *rGraph = graph.getResidualGraph(true);
  // shortestAugmentingPath(rGraph);
  // graph.fillGraphFromResidual(rGraph);
  // graph.print();
  // cout << endl;

  // cout << endl;

  //cout << "Max flow: " << graph.getValueObjMaxFlow() << endl;
  //saveSolution(&graph, "../sol/maxflow_1");
  //validFlow(&graph);

  // Graph graphMin = mincost::parse("../data/mincost/simple_min_cost.min");
  // PL::minCostFlow(graphMin);

  // Test Preflow Push
  // Graph graph = maxflow::parse("../data/simple_max_flot.max");
  // preflowPush(&graph);

  // cycleCancelling(&graph);

  // Problème: on trouve pas la même solution pour l'algo et le solveur...
  return 0;
}
