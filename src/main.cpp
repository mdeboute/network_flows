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
<<<<<<< HEAD
  maxFlowComparison("../data/maxflow/maxFlowTest100v1000e.max",true);
  //maxFlowBenchmarks(true);

  //graph.print();
  //cout << endl;
  //cout << "Residual graph:\n";
  //cout << endl;
  //Graph graphMax = maxflow::parse("../data/maxflow/instance_1.max");
  //PL::maxFlow(graphMax);
=======
  maxFlowComparison("../data/maxflow/maxFlowTest500v5000e.max");

  // Graph graph = maxflow::parse("../data/maxflow/maxFlowTest600v6000e.max");
  // graph.print();
  // cout << endl;
  // cout << "Residual graph:\n";
  // cout << endl;
  // Graph graphMax = maxflow::parse("../data/maxflow/maxFlowTest600v6000e.max");
  // PL::maxFlow(graphMax);
>>>>>>> e3bb3502d6a31ca2bc4fee286815649ba00d5bec

  // graph.removeLonelyNodes();
  // Graph *rGraph = graph.getResidualGraph(true);
  // shortestAugmentingPath(rGraph);
  // graph.fillGraphFromResidual(rGraph);
  // graph.print();
  // cout << endl;

  // cout << endl;

<<<<<<< HEAD
  //cout << "Max flow: " << graph.getValueObjMaxFlow() << endl;
  //saveSolution(&graph, "../sol/maxflow_1");
  //validFlow(&graph);
=======
  // cout << "Max flow: " << graph.getValueObjMaxFlow() << endl;
  // saveSolution(&graph, "../sol/maxflow_1");
  // validFlow(&graph);
>>>>>>> e3bb3502d6a31ca2bc4fee286815649ba00d5bec

  // Graph graphMin = mincost::parse("../data/mincost/simple_min_cost.min");
  // PL::minCostFlow(graphMin);

  // Test Preflow Push
  // Graph graph = maxflow::parse("../data/simple_max_flot.max");
  // preflowPush(&graph);

  // cycleCancelling(&graph);

  // Problème: on trouve pas la même solution pour l'algo et le solveur...
  return 0;
}
