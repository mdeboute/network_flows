#include <iostream>
#include "Structures.hpp"

// getters de la classe Vertex
Edge &Vertex::getEnteringEdge(Graph &graph, int id) { return graph.edges[enteringEdgesId[id]]; }
Edge &Vertex::getLeavingEdge(Graph &graph, int id) { return graph.edges[leavingEdgesId[id]]; }
Vertex &Vertex::getEnteringNeighbour(Graph &graph, int id) { return graph.vertices[getEnteringEdge(graph, id).startId]; }
Vertex &Vertex::getLeavingNeighbour(Graph &graph, int id) { return graph.vertices[getLeavingEdge(graph, id).endId]; }

// getters de la classe Edge
Vertex &Edge::getStart(Graph &graph) { return graph.vertices[startId]; }
Vertex &Edge::getEnd(Graph &graph) { return graph.vertices[endId]; }
Edge &Edge::getPairedEdge(Graph &graph) { return graph.edges[pairedEdgeId]; }

// getters de la classe Graph
Edge &Graph::getEnteringEdge(int vertexId, int edgeId) { return vertices[vertexId].getEnteringEdge(*this, edgeId); }
Edge &Graph::getLeavingEdge(int vertexId, int edgeId) { return vertices[vertexId].getLeavingEdge(*this, edgeId); }
Vertex &Graph::getEnteringNeighbour(int vertexId, int neighbourId) { return vertices[vertexId].getEnteringNeighbour(*this, neighbourId); }
Vertex &Graph::getLeavingNeighbour(int vertexId, int neighbourId) { return vertices[vertexId].getLeavingNeighbour(*this, neighbourId); }
Vertex &Graph::getStart(int edgeId) { return edges[edgeId].getStart(*this); }
Vertex &Graph::getEnd(int edgeId) { return edges[edgeId].getEnd(*this); }
Edge &Graph::getPairedEdge(int edgeId) { return edges[edgeId].getPairedEdge(*this); }

//à ajouter le booléen qui indique la fusion des arcs parallèles
Graph *Graph::getResidualGraph()
{
  Graph *residualGraph = new Graph(nbVertices);
  residualGraph->src = src;
  residualGraph->sink = sink;

  for (Edge &edge : edges)
  { // usage d'une référence sinon on itère sur des copies

    // arc résiduel
    int id = residualGraph->nbEdges;
    int cost = edge.cost;
    int startId = edge.startId;
    int endId = edge.endId;

    Edge residualEdge(id, cost, 0, 0, startId, endId);
    residualEdge.residualCapacity = edge.maxCapacity - edge.flow;
    residualEdge.pairedEdgeId = id + 1;

    // arc résiduel inverse
    int invId = id + 1;
    int invCost = -edge.cost;
    int invStartId = edge.endId;
    int invEndId = edge.startId;

    Edge inverseEdge(invId, invCost, 0, 0, invStartId, invEndId);
    inverseEdge.residualCapacity = edge.flow;
    inverseEdge.pairedEdgeId = id;

    residualGraph->addEdge(residualEdge);
    residualGraph->addEdge(inverseEdge);
  }
  return residualGraph;
}

// la capacité résiduelle de l'arc inverse est changée automatiquement
void Edge::increaseResidualCapacity(Graph &graph,int increase)
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
void Edge::setResidualCapacity(Graph &graph,int newCap){
  int increase = newCap - residualCapacity;
  this->increaseResidualCapacity(graph,increase);
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

void Graph::increaseFlow(int edgeId, int increase) { edges[edgeId].increaseFlow(increase); }
void Graph::setFlow(int edgeId, int newFlow) { edges[edgeId].setFlow(newFlow); }

void Graph::addVertex()
{
  Vertex newVertex(nbVertices);
  vertices.push_back(newVertex);
  nbVertices += 1;
}

void Graph::addEdge(Edge edge)
{
  edges.push_back(edge);

  vertices[edge.startId].nbLeavingEdges += 1;
  vertices[edge.startId].leavingEdgesId.push_back(nbEdges);

  vertices[edge.endId].nbEnteringEdges += 1;
  vertices[edge.endId].enteringEdgesId.push_back(nbEdges);

  nbEdges += 1;
}
