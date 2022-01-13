#include "Structures.cpp"
#include "Manipulation.cpp"
#include "MinCostParser.cpp"



int main()
{
  // {cost,min,max,start,end} -> arête du sommet start vers end, avec coût cost, capacité minimum min et maximum max
  int edgeArray[][5] = {{3,2,10,0,1},{1,0,4,1,2},{4,1,3,1,3},{2,0,5,2,3}};
  Graph graph(4,4,edgeArray);

  graph.increaseFlow(0,4);
  graph.increaseFlow(1,1);
  graph.increaseFlow(2,3);
  graph.increaseFlow(3,1);

  Graph* residualGraph = graph.getResidualGraph();

  graph.print();
  std::cout << "\n";
  residualGraph->print();

  Graph g parse("../data/mincost/gte_bad.20");
  g.print();

  return 0;
}
