#include <iostream>
#include <ctime>
#include <fstream>
#include "benchmarks.hpp"
#include "Graph.hpp"
#include "parser.hpp"
#include "algorithms.hpp"
#include "checker.hpp"
#include "saver.hpp"
#include "PLFlows.hpp"

void doAllBenchmarks()
{
  maxFlowBenchmarks(false, true, 10, "../data/maxflow/4k40k/", "inst_4000_40000_");
  std::cout << "\n";
  maxFlowBenchmarks(false, true, 10, "../data/maxflow/6k60k/", "inst_6000_60000_");
  std::cout << "\n";
  maxFlowBenchmarks(false, true, 10, "../data/maxflow/8k80k/", "inst_8000_80000_");
  std::cout << "\n";
  maxFlowBenchmarks(false, true, 10, "../data/maxflow/10k100k/", "inst_10000_100000_");

  std::cout << "\n";

  minCostBenchmarks(true, 10, "../data/mincost/4k40k/", "inst_4000_40000_");
  std::cout << "\n";
  minCostBenchmarks(true, 10, "../data/mincost/6k60k/", "inst_6000_60000_");
  std::cout << "\n";
  minCostBenchmarks(true, 10, "../data/mincost/8k80k/", "inst_8000_80000_");
  std::cout << "\n";
  minCostBenchmarks(true, 10, "../data/mincost/10k100k/", "inst_10000_100000_");
}

bool minCostBenchmarks(bool checkWithLP, int fileAmount, std::string fileDirectory, std::string fileFamily)
{
  int timer1 = 0;
  int timer3 = 0;
  int validTestsAmount = 0;

  for (int index = 1; index <= fileAmount; index++)
  {
    std::string fileName = fileFamily + std::to_string(index) + ".max.min";
    std::string filePath = fileDirectory + fileName;

    if (minCostComparison(filePath, fileName, true, &timer1, &timer3))
    {
      validTestsAmount++;
    }
    std::cout << validTestsAmount << " valid tests, CC total time: " << timer1 << ", LP total time: " << timer3 << "\n";
  }

  return true;
}

bool minCostComparison(std::string filePath, std::string fileName, bool checkWithLP, int *timer1, int *timer3)
{
  std::cout << "MinCost comparison on " << fileName << "\n";

  int value3;
  int duration3;
  if (checkWithLP)
  {
    Graph graph3 = minCost::parse(filePath, false);
    Graph expGraph3 = minCost::parse(filePath, false);
    setMaxPossibleFlow(&graph3, &expGraph3);
    int startTime3 = time(NULL);
    value3 = PL::minCost(graph3);
    duration3 = time(NULL) - startTime3;
    if (timer3 != NULL and value3 != -1)
    {
      *timer3 += duration3;
    }
    std::cout << "LP duration: " << duration3 << " seconds\n";
  }

  if (value3 == -1)
  {
    std::cout << "Infeasible\n";
    Graph graph1 = minCost::parse(filePath, false);
    Graph expGraph1 = minCost::parse(filePath, false);
    setMaxPossibleFlow(&graph1, &expGraph1);
    cycleCancelling(&graph1);
    int value1 = graph1.getValueObjMinCost();
    if (value1 != 0)
    {
      std::cerr << "Error: LP says infeasible but CC objective value is " << value1 << "\n";
    }
    return false;
  }

  Graph graph1 = minCost::parse(filePath, false);
  Graph expGraph1 = minCost::parse(filePath, false);
  setMaxPossibleFlow(&graph1, &expGraph1);
  // Cycle cancelling
  int startTime1 = time(NULL);
  cycleCancelling(&graph1);
  int duration1 = time(NULL) - startTime1;
  if (timer1 != NULL)
  {
    *timer1 += duration1;
  }
  std::cout << "Cycle Cancelling: " << duration1 << " seconds\n";

  // on vérifie la validité des solutions
  int value1 = graph1.getValueObjMinCost();

  if (not validFlow(&graph1))
  {
    std::cerr << "Error: invalid flow from Cycle Cancelling\n";
    return false;
  }

  if (checkWithLP and value3 != value1)
  {
    std::cout << "LP: " << value3 << "\n";
    std::cout << "Cycle Cancelling: " << value1 << "\n";
    std::cerr << "Error: different objective values\n";
    return false;
  }

  // si tout est valide on sauvegarde la solution et les temps
  std::string solName = "../solution/sol_" + fileName;
  saveSolution(&graph1, solName);

  std::string timeName = "../solution/time_" + fileName;
  std::ofstream timeFile;
  timeFile.open(timeName);
  if (not timeFile.is_open())
  {
    std::cout << "Failed to create file!\n";
  }

  timeFile << std::to_string(graph1.nbVertices) << " vertices, " << std::to_string(graph1.nbEdges) << " edges"
           << "\n";
  timeFile << "Value: " << std::to_string(value1) << "\n";
  timeFile << "Cycle Cancelling: " << std::to_string(duration1) << "\n";
  if (checkWithLP)
  {
    timeFile << "LP: " << std::to_string(duration3) << "\n";
  }
  timeFile.close();

  return true;
}

bool maxFlowBenchmarks(bool usePrepush, bool checkWithLP, int fileAmount, std::string fileDirectory, std::string fileFamily)
{
  int timer1 = 0;
  int timer2 = 0;
  int timer3 = 0;
  int validTestsAmount = 0;

  for (int index = 1; index <= fileAmount; index++)
  {
    std::string fileName = fileFamily + std::to_string(index) + ".max";
    std::string filePath = fileDirectory + fileName;

    if (maxFlowComparison(filePath, fileName, usePrepush, true, &timer1, &timer2, &timer3))
    {
      validTestsAmount++;
    }
    std::cout << validTestsAmount << "Valid tests, SAP total time: " << timer1 << ", LP total time: " << timer3 << "\n";
    if (usePrepush)
    {
      std::cout << "PPF total time: " << timer2 << "\n";
    }
  }

  return true;
}

bool maxFlowComparison(std::string filePath, std::string fileName, bool usePrepush, bool checkWithLP, int *timer1, int *timer2, int *timer3)
{
  std::cout << "Maxflow comparison on " << fileName << "\n";

  Graph graph1 = maxFlow::parse(filePath, false);
  Graph graph2 = maxFlow::parse(filePath, false);

  int startTime2;
  int duration2;
  int value2;
  if (usePrepush)
  {
    // Preflow Push
    startTime2 = time(NULL);
    preflowPush(&graph2);
    duration2 = time(NULL) - startTime2;
    value2 = graph2.getValueObjMaxFlow();
    if (timer2 != NULL and value2 != 0)
    {
      *timer2 += duration2;
    }

    std::cout << "Preflow Push duration: " << duration2 << " seconds\n";
  }

  // Shortest Augmenting Path
  int startTime1 = time(NULL);
  shortestAugmentingPath(&graph1);
  int duration1 = time(NULL) - startTime1;
  int value1 = graph1.getValueObjMaxFlow();
  if (timer1 != NULL and value1 != 0)
  {
    *timer1 += duration1;
  }
  std::cout << "Shortest Augmenting Path duration: " << duration1 << " seconds\n";

  int value3;
  int duration3;
  if (checkWithLP)
  {
    Graph graph3 = maxFlow::parse(filePath, false);
    int startTime3 = time(NULL);
    value3 = PL::maxFlow(graph3);
    duration3 = time(NULL) - startTime3;
    if (timer3 != NULL and value3 != 0)
    {
      *timer3 += duration3;
    }
    std::cout << "LP duration: " << duration3 << " seconds\n";
  }

  if (not validFlow(&graph1))
  {
    std::cerr << "Error: invalid flow from Shortest Augmenting Path\n";
    return false;
  }

  if (usePrepush and not validFlow(&graph2))
  {
    std::cerr << "Error: invalid flow from Preflow Push\n";
    return false;
  }

  if (usePrepush and value1 != value2)
  {
    std::cout << "Shortest Augmenting Path: " << value1 << "\n";
    std::cout << "Preflow Push: " << value2 << "\n";
    std::cerr << "Error: different objective values\n";
    return false;
  }

  if (checkWithLP and (value3 != value1 or (usePrepush and value3 != value2)))
  {
    std::cout << "LP: " << value3 << "\n";
    std::cout << "Both algorithm: " << value1 << "\n";
    std::cerr << "Error: different objective values\n";
    return false;
  }

  if (value1 == 0)
  {
    std::cout << "Infeasible\n";
    return false;
  }

  // si tout est valide on sauvegarde la solution et les temps
  std::string solName = "../solution/sol_" + fileName;
  saveSolution(&graph1, solName);

  std::string timeName = "../solution/time_" + fileName;
  std::ofstream timeFile;
  timeFile.open(timeName);
  if (not timeFile.is_open())
  {
    std::cerr << "Failed to create file!\n";
  }

  timeFile << std::to_string(graph1.nbVertices) << " vertices, " << std::to_string(graph1.nbEdges) << " edges"
           << "\n";
  timeFile << "Value: " << std::to_string(value1) << "\n";
  timeFile << "Shortest Augmenting Path: " << std::to_string(duration1) << "\n";

  if (usePrepush)
  {
    timeFile << "Preflow Push: " << std::to_string(duration2) << "\n";
  }
  if (checkWithLP)
  {
    timeFile << "LP: " << std::to_string(duration3) << "\n";
  }
  timeFile.close();

  return true;
}
