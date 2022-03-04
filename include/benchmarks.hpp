#ifndef BENCHMARKS_HPP
#define BENCHMARKS_HPP

#include <iostream>

bool maxFlowComparison(std::string filePath, std::string filename, bool usePrepush, bool checkWithLP,int* timer1,int* timer2,int* timer3);

bool maxFlowBenchmarks(bool usePrepush, bool checkWithLP,int fileAmount,std::string fileDirectory,std::string fileFamily);

bool minCostComparison(std::string filePath, std::string filename, bool checkWithLP,int* timer1,int* timer3);

bool minCostBenchmarks(bool checkWithLP,int fileAmount,std::string fileDirectory,std::string fileFamily);

void doAllBenchmarks();

#endif
