#include "saver.hpp"
#include "Graph.hpp"
#include <iostream>
#include <fstream>

void saveSolution(Graph *graph, std::string filename)
{
  int suppliedEdgesAmount = 0;
  std::string flowLines = "";
  for (Edge edge : graph->edges)
  {
    if (edge.flow > 0)
    {
      flowLines += std::to_string(edge.startId) + " " + std::to_string(edge.endId) + " " + std::to_string(edge.flow) + "\n";
      suppliedEdgesAmount++;
    }
  }
  std::string firstLine = std::to_string(suppliedEdgesAmount) + "\n";
  std::string lines = firstLine + flowLines;

  std::ofstream solutionFile;
  solutionFile.open(filename);
  solutionFile << lines;
  solutionFile.close();
}
