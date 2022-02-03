#include "Structures.cpp"
#include "Manipulation.cpp"
#include "MinCostParser.cpp"
#include "MaxFlowParser.cpp"


int main()
{
  Graph graph = parse("../data/mincost/test.txt");
  graph.print();
  std::cout << std::endl;
  std::cout << "Residual graph:\n" << std::endl;
  Graph* rGraph = graph.getResidualGraph();
  rGraph->print();

  std::cout << std::endl;
  Graph graph2 = maxFlowParser("../data/maxflow/instance_1.max");
  //graph2.print();

  //TODO:
  //inclure les headers (en créer si besoin) et non les fichiers .cpp
  //les protéger avec des #ifndef et #define

  return 0;
}
