#ifndef BENCHMARKS_HPP
#define BENCHMARKS_HPP

#include <iostream>



bool maxFlowComparison(std::string fileName,bool checkWithLP);

bool maxFlowBenchmarks(bool checkWithLP);



bool minCostComparison(std::string fileName,bool checkWithLP);

bool minCostBenchmarks(bool checkWithLP);



#endif
