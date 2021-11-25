#include "Structures.cpp"
#include "Manipulation.cpp"



int main()
{
  // {s,e,w,c} -> arête du sommet s vers e, avec pois w et capacité c
  int edgeArray[][4] = {{0,1,5,10},{1,2,6,8},{0,2,5,9},{3,1,4,11},{3,0,5,5}};
  Graph graph(4,5,edgeArray);
  graph.print();

  graph.edges[0].flow = 2;
  graph.edges[1].flow = 2;
  graph.edges[2].flow = 3;
  graph.edges[3].flow = 2;
  graph.edges[4].flow = 5;

  std::cout << "\n";
  Graph* residualGraph = graph.getResidualGraph();
  residualGraph->print();

  return 0;
}
