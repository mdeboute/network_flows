#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include "Graph.hpp"

namespace mincost
{
    void openFile(std::ifstream &file, std::string filePath);
    Graph processFile(std::ifstream &file);
    Graph parse(std::string filePath);
}

namespace maxflow
{
    void openFile(std::ifstream &file, std::string filePath);
    Graph processFile(std::ifstream &file);
    Graph parse(std::string filePath);
}

#endif