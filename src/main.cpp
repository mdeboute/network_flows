#include <iostream>
#include "Structures.hpp"
#include "parser.hpp"
#include "algorithms.hpp"
using namespace std;

int main()
{

  // int edgeArray[][3] = {{0,1,10},{0,2,3},{1,2,4},{1,3,5},{2,3,8}}; ??? (fait un fichier)
  // Graph graph(4,5,0,3,edgeArray);
  // graph.edges[0].increaseFlow(2);
  // graph.edges[2].increaseFlow(2);
  // graph.edges[4].increaseFlow(2);
  // graph.print();
  // std::cout << "Residual graph\n\n";
  // Graph *rGraph = graph.getResidualGraph();
  // rGraph->print();

  // Graph graph = mincost::parse("../data/negative_weight_cycle.min");
  // graph.print();
  // cout << endl;
  // cout << "Residual graph:\n"
  //      << endl;
  // Graph *rGraph = graph.getResidualGraph();
  // rGraph->print();

  // cout << endl;
  // BellmanFord(graph, 0);
  // ==> it works

  Graph graph = maxflow::parse("../data/instance_with_path.max");
  graph.print();

  cout << endl;
  cout << "Residual graph:\n"
       << endl;
  Graph *rGraph = graph.getResidualGraph();
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
