#include <iostream>
#include <ctime>
#include <fstream>
#include "benchmarks.hpp"
#include "Graph.hpp"
#include "parser.hpp"
#include "algorithm.hpp"
#include "PreflowPush.hpp"
#include "checker.hpp"
#include "saver.hpp"
#include "PLFlows.hpp"



bool maxFlowBenchmarks(bool checkWithLP)
{
  std::string fileList[10];
  for(int index = 0;index<10;index++)
  {
    fileList[index]="../generator/maxflow/debug"+std::to_string(index)+".max";
  }


  for(std::string fileName:fileList)
  {
    if(not maxFlowComparison(fileName,checkWithLP)){return false;}
  }

  return true;
}



bool maxFlowComparison(std::string fileName,bool checkWithLP)
{
  std::string localName = fileName.substr(16);
  std::cout << "Maxflow comparison on " << localName << "\n";

  Graph graph1 = maxflow::parse(fileName,false);
  Graph graph2 = maxflow::parse(fileName,false);

  //Shortest Augmenting Path
  int startTime1 = time(NULL);
  Graph *residualGraph = graph1.getResidualGraph(true);
  shortestAugmentingPath(residualGraph);
  graph1.fillGraphFromResidual(residualGraph);
  int duration1 = time(NULL) - startTime1;

  std::cout << "Shortest Augmenting Path duration: " << duration1 << " seconds\n";

  //Preflow Push
  int startTime2 = time(NULL);
  preflowPush(&graph2);
  int duration2 = time(NULL) - startTime2;

  std::cout << "Preflow Push duration: " << duration2 << " seconds\n";

  int value3;
  int duration3;
  if(checkWithLP)
  {
    Graph graph3 = maxflow::parse(fileName,false);
    int startTime3 = time(NULL);
    value3 = PL::maxFlow(graph3);
    duration3 = time(NULL) - startTime3;
    std::cout << "LP duration: " << duration3 << " seconds\n";
  }

  //on vérifie la validité des solutions
  int value1 = graph1.getValueObjMaxFlow();
  int value2 = graph2.getValueObjMaxFlow();

  if(not validFlow(&graph1))
  {
    std::cout << "Error: invalid flow from Shortest Augmenting Path\n";
    return false;
  }

  if(not validFlow(&graph2))
  {
    std::cout << "Error: invalid flow from Preflow Push\n";
    return false;
  }

  if(value1 != value2)
  {
    std::cout << "Shortest Augmenting Path: " << value1 << "\n";
    std::cout << "Preflow Push: " << value2 << "\n";
    std::cout << "Error: different objective values\n";
    return false;
  }

  if(checkWithLP and (value3 != value1 or value3 != value2))
  {
    std::cout << "LP: " << value3 << "\n";
    std::cout << "Both algorithm: " << value1 << "\n";
    std::cout << "Error: different objective values\n";
    return false;
  }

  saveSolution(&graph1, "../solution/sol_"+localName);

  std::fstream timeFile;
  timeFile.open("../solution/time_"+localName);
  if(not timeFile.is_open()){std::cout << "pas réussi à créer le fichier\n";}
  timeFile << std::to_string(graph1.nbVertices) << " vertices, " << std::to_string(graph1.nbEdges) << " edges"<< "\n";
  timeFile << "Shortest Augmenting Path: " << std::to_string(duration1) << "\n";
  timeFile << "Preflow Push: " << std::to_string(duration2) << "\n";
  if(checkWithLP){timeFile << "LP: " << std::to_string(duration3) << "\n";}
  timeFile.close();

  return true;
}
