#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include "Graph.hpp"

namespace mincost
{
    void openFile(std::ifstream &file, std::string filePath);
    void openFile(std::ifstream &file, std::string filePath,bool verbose);
    Graph processFile(std::ifstream &file);
    Graph processFile(std::ifstream &file,bool verbose);
    Graph parse(std::string filePath);
    Graph parse(std::string filePath,bool verbose);
}

namespace maxflow
{
    void openFile(std::ifstream &file, std::string filePath);
    void openFile(std::ifstream &file, std::string filePath,bool verbose);
    Graph processFile(std::ifstream &file);
    Graph processFile(std::ifstream &file,bool verbose);
    Graph parse(std::string filePath);
    Graph parse(std::string filePath,bool verbose);
}

#endif
