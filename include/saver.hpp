#ifndef SAVER_HPP
#define SAVER_HPP

#include "Graph.hpp"
#include <iostream>
#include <fstream>

void saveSolution(Graph *graph, std::string filename);
void saveSolution(Graph *graph, std::string filename,int time);

#endif
