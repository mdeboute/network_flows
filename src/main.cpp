#include "Structures.cpp"
#include "Manipulation.cpp"



int main()
{
  // {cost,min,max,start,end} -> arête du sommet start vers end, avec coût cost, capacité minimum min et maximum max
  int edgeArray[][5] = {{3,2,10,0,1},{1,0,4,1,2},{4,1,3,1,3},{2,0,5,2,3}};
  Graph graph(4,4,edgeArray);
  Graph* residualGraph = graph.getResidualGraph();

  graph.edges[0].increaseFlow(*residualGraph,4);
  graph.edges[1].increaseFlow(*residualGraph,1);
  graph.edges[2].increaseFlow(*residualGraph,3);
  graph.edges[3].increaseFlow(*residualGraph,1);

  graph.print();
  std::cout << "\n";
  residualGraph->print();

  return 0;
}
