#include "Structures.hpp"



//getters de la classe Vertex
Edge& Vertex::getEnteringEdge(Graph& graph,int id){return graph.edges[enteringEdgesId[id]];}
Edge& Vertex::getLeavingEdge(Graph& graph,int id){return graph.edges[leavingEdgesId[id]];}
Vertex& Vertex::getEnteringNeighbour(Graph& graph,int id){return graph.vertices[getEnteringEdge(graph,id).startId];}
Vertex& Vertex::getLeavingNeighbour(Graph& graph,int id){return graph.vertices[getLeavingEdge(graph,id).endId];}



//getters de la classe Edge
Vertex& Edge::getStart(Graph& graph){return graph.vertices[startId];}
Vertex& Edge::getEnd(Graph& graph){return graph.vertices[endId];}
Edge& Edge::getPairedEdge(Graph& pairedGraph){return pairedGraph.edges[pairedEdgeId];}



//ces méthodes prennent en charge le changement de flot dans le graphe asscocié
void Edge::increaseFlow(Graph& pairedGraph,int increase)
{
  flow += increase;
  getPairedEdge(pairedGraph).maxCapacity += -increase;

  if(flow < minCapacity){std::cout << "Capacité minimale non respectée sur l'arc " << id << "\n";}
  if(flow > maxCapacity){std::cout << "Capacité maximale non respectée sur l'arc " << id << "\n";}
}
void Edge::setFlow(Graph& pairedGraph,int newFlow)
{
  int increase = newFlow - flow;
  increaseFlow(pairedGraph,increase);
}



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



Graph* Graph::getResidualGraph()
{
  Graph* residualGraph = new Graph(nbVertices);

  for(Edge& edge : edges){ //usage d'une référence sinon on itère sur des copies

    int residualCapacity = edge.maxCapacity - edge.flow;

    if(residualCapacity > 0){

      int id = residualGraph->nbEdges;
      int cost = edge.cost;
      int minCapacity = 0;
      int maxCapacity = residualCapacity;
      int startId = edge.endId;
      int endId = edge.startId;

      Edge residualEdge(id,cost,minCapacity,maxCapacity,startId,endId);
      residualEdge.pairedEdgeId = edge.id;
      edge.pairedEdgeId = residualGraph->nbEdges;

      residualGraph->addEdge(residualEdge);
    }
  }

  pairedGraph = residualGraph;
  residualGraph->pairedGraph = this;
  return residualGraph;
}
