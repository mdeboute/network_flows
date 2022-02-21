#include "saver.hpp"
#include "Graph.hpp"
#include <iostream>
#include <fstream>

void saveSolution(Graph *graph, std::string filename, int time)
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
  std::string timeLine = std::to_string(time) + "\n";
  std::string sizeLine = std::to_string(suppliedEdgesAmount) + "\n";
  std::string lines = timeLine + sizeLine + flowLines;

  std::ofstream solutionFile;
  solutionFile.open(filename);
  solutionFile << lines;
  solutionFile.close();
}

void saveSolution(Graph *graph, std::string filename)
{
  saveSolution(graph, filename, -1);
}
