#include <iostream>
#include <cstdint>
#include "Graph.hpp"
#include "ortools/graph/max_flow.h"
#include "ortools/graph/min_cost_flow.h"

namespace PLNE
{
  void maxFlow(Graph &graph, int begin, int end)
  {
    SimpleMaxFlow max_flow;

    std::vector<int64_t> start_nodes[graph.nbEdges];
    std::vector<int64_t> end_nodes[graph.nbEdges];
    std::vector<int64_t> capacities[graph.nbEdges];

    for (int i = 0; i < graph.nbEdges; i++)
    {
      start_nodes[i] = graph.edges[i].startId;
      end_nodes[i] = graph.edges[i].endId;
      capacities[i] = graph.edges[i].maxCapacity;
    }

    for (int i = 0; i < start_nodes.size(); ++i)
    {
      max_flow.AddArcWithCapacity(start_nodes[i], end_nodes[i], capacities[i]);
    }

    int status = max_flow.Solve(begin, end);

    if (status == MaxFlow::OPTIMAL)
    {
      LOG(INFO) << "Max flow: " << max_flow.OptimalFlow();
      LOG(INFO) << "";
      LOG(INFO) << "  Arc    Flow / Capacity";
      for (std::size_t i = 0; i < max_flow.NumArcs(); ++i)
      {
        LOG(INFO) << max_flow.Tail(i) << " -> " << max_flow.Head(i) << "  "
                  << max_flow.Flow(i) << "  / " << max_flow.Capacity(i);
      }
    }
    else
    {
      LOG(INFO) << "Solving the max flow problem failed. Solver status: "
                << status;
    }
  }

  // MinCostFlow simple interface example.
  void minCostFlow(Graph &graph)
  {
    // Instantiate a SimpleMinCostFlow solver.
    SimpleMinCostFlow min_cost_flow;

    std::vector<int64_t> start_nodes[graph.nbEdges];
    std::vector<int64_t> end_nodes[graph.nbEdges];
    std::vector<int64_t> capacities[graph.nbEdges];
    std::vector<int64_t> unit_costs[graph.nbEdges];
    std::vector<int64_t> supplies[graph.nbEdges];

    for (int i = 0; i < graph.nbEdges; i++)
    {
      start_nodes[i] = graph.edges[i].startId;
      end_nodes[i] = graph.edges[i].endId;
      capacities[i] = graph.edges[i].maxCapacity;
      unit_costs[i] = graph.edges[i].cost;
      supplies[i] = graph.edges[i].minCapacity;
    }

    // Add each arc.
    for (int i = 0; i < start_nodes.size(); ++i)
    {
      int arc = min_cost_flow.AddArcWithCapacityAndUnitCost(
          start_nodes[i], end_nodes[i], capacities[i], unit_costs[i]);
      if (arc != i)
        LOG(FATAL) << "Internal error";
    }

    // Add node supplies.
    for (int i = 0; i < supplies.size(); ++i)
    {
      min_cost_flow.SetNodeSupply(i, supplies[i]);
    }

    // Find the min cost flow.
    int status = min_cost_flow.Solve();

    if (status == MinCostFlow::OPTIMAL)
    {
      LOG(INFO) << "Minimum cost flow: " << min_cost_flow.OptimalCost();
      LOG(INFO) << "";
      LOG(INFO) << " Arc   Flow / Capacity  Cost";
      for (std::size_t i = 0; i < min_cost_flow.NumArcs(); ++i)
      {
        int64_t cost = min_cost_flow.Flow(i) * min_cost_flow.UnitCost(i);
        LOG(INFO) << min_cost_flow.Tail(i) << " -> " << min_cost_flow.Head(i)
                  << "  " << min_cost_flow.Flow(i) << "  / "
                  << min_cost_flow.Capacity(i) << "       " << cost;
      }
    }
    else
    {
      LOG(INFO) << "Solving the min cost flow problem failed. Solver status: "
                << status;
    }
  }

}
