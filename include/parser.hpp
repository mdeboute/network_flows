#ifndef PARSER_HPP
#define PARSER_HPP
#include <iostream>
#include <sstream>
#include <fstream>
#include "Structures.hpp"

namespace mincost
{
    void openFile(std::ifstream &file, std::string filePath);
    Graph processFile(std::ifstream &file);
    Graph parse(std::string filePath);
} // namespace mincost

namespace maxflow
{
    void openFile(std::ifstream &file, std::string filePath);
    Graph processFile(std::ifstream &file);
    Graph parse(std::string filePath);
} // namespace maxflow

#endif