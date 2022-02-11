#include <iostream>
#include "Graph.hpp"
#include "parser.hpp"
#include "algorithm.hpp"
using namespace std;

int main()
{
  Graph graph = mincost::parse("../data/negative_weight_cycle.min");
  graph.print();
  cout << endl;
  cout << "Residual graph:\n"
       << endl;
  Graph *rGraph = graph.getResidualGraph();
  rGraph->print();

  cout << endl;
  BellmanFord(graph, 0);
  // ==> it works

  Graph graph = maxflow::parse("../data/instance_with_path.max");
  graph.print();

  cout << endl;
  cout << "Residual graph:\n"
       << endl;
  Graph *rGraph = graph.getResidualGraph(true);
  rGraph->print();

  int parent[graph.nbVertices];
  bool hasPath = bfs(rGraph, rGraph->src, rGraph->sink, parent);
  if (hasPath)
  {
    cout << "Path found" << endl;
  }
  else
  {
    cout << "No path found" << endl;
  }

  // TODO: fix getResidualGraph(), on doit trouver un chemin sur l'exemple ci-dessus
  return 0;
}
