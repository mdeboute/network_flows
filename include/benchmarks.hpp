#ifndef BENCHMARKS_HPP
#define BENCHMARKS_HPP

#include <iostream>



bool maxFlowComparison(std::string filePath,std::string filename,bool checkWithLP);

bool maxFlowBenchmarks(bool checkWithLP);



bool minCostComparison(std::string filePath,std::string filename,bool checkWithLP);

bool minCostBenchmarks(bool checkWithLP);

#endif
