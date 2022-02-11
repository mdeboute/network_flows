#include <iostream>
#include <vector>
#include "Edge.hpp"
#include "Graph.hpp"

Edge::Edge(int id, int cost, int minCapacity, int maxCapacity, int startId, int endId)
{
    this->id = id;
    this->cost = cost;
    this->minCapacity = minCapacity;
    this->maxCapacity = maxCapacity;
    residualCapacity = 0;
    this->startId = startId;
    this->endId = endId;
    this->flow = 0;
    pairedEdgeId = -1;
    mirrorEdgeId = -1;
}

Edge::Edge(int id, int startId, int endId, int maxCapacity)
{
    this->id = id;
    this->cost = 0;
    this->minCapacity = 0;
    this->maxCapacity = maxCapacity;
    residualCapacity = 0;
    this->startId = startId;
    this->endId = endId;
    this->flow = 0;
    pairedEdgeId = -1;
    mirrorEdgeId = -1;
}

void Edge::print()
{
    std::cout << "Edge " << id << ": from V" << startId << " to V" << endId;
    std::cout << ", flow " << flow << ", minCap " << minCapacity << ", maxCap " << maxCapacity << ", resCap " << residualCapacity << ", cost " << cost << "\n";
}

// la capacité résiduelle de l'arc inverse est changée automatiquement
void Edge::increaseResidualCapacity(Graph &graph, int increase)
{
    residualCapacity += increase;

    Edge &pairedEdge = getPairedEdge(graph);
    pairedEdge.residualCapacity += -increase;

    if (residualCapacity < 0 or pairedEdge.residualCapacity < 0)
    {
        std::cout << "Changement de capacité résiduelle impossible, arc " << id << "\n";
    }
}

// la capacité résiduelle de l'arc inverse est changée automatiquement
void Edge::setResidualCapacity(Graph &graph, int newCap)
{
    int increase = newCap - residualCapacity;
    this->increaseResidualCapacity(graph, increase);
}

// ces méthodes ne prennent pas en charge le changement dans le graphe résiduel
void Edge::increaseFlow(int increase)
{
    flow += increase;

    if (flow < minCapacity)
    {
        std::cout << "Capacité minimale non respectée sur l'arc " << id << "\n";
    }
    if (flow > maxCapacity)
    {
        std::cout << "Capacité maximale non respectée sur l'arc " << id << "\n";
    }
}

void Edge::setFlow(int newFlow)
{
    int increase = newFlow - flow;
    increaseFlow(increase);
}

// getters de la classe Edge
Vertex &Edge::getStart(Graph &graph) { return graph.vertices[startId]; }
Vertex &Edge::getEnd(Graph &graph) { return graph.vertices[endId]; }
Edge &Edge::getPairedEdge(Graph &graph) { return graph.edges[pairedEdgeId]; }
