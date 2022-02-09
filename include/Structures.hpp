#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP
#include <vector>

class Edge;
class Graph;

class Vertex
{
public:
  // attributs
  int id;
  int exceedingFlow;
  int nbEnteringEdges;
  int nbLeavingEdges;
  std::vector<int> enteringEdgesId;
  std::vector<int> leavingEdgesId;

  // méthodes
  Vertex(int id, int exceedingFlow);
  Vertex(int id);
  void print();
  Edge &getEnteringEdge(Graph &graph, int id);        // retourne la n-ième arête entrante (n=id)
  Edge &getLeavingEdge(Graph &graph, int id);         // retourne la n-ième arête sortante (n=id)
  Vertex &getEnteringNeighbour(Graph &graph, int id); // retourne le n-ième voisin entrant (n=id)
  Vertex &getLeavingNeighbour(Graph &graph, int id);  // retourne le n-ième voisin sortant (n=id)
};

class Edge
{
public:
  // attributs
  int id;
  int cost;
  int minCapacity;
  int maxCapacity;
  int residualCapacity;
  int flow;
  int startId;
  int endId;
  int pairedEdgeId;

  // méthodes
  Edge(int id, int cost, int minCapacity, int maxCapacity, int startId, int endId);
  Edge(int id, int startId, int endId, int maxCapacity);
  void print();
  void increaseFlow(int increase); // les négatifs sont tolérés
  void setFlow(int newFlow);
  void increaseResidualCapacity(Graph &graph,int increase); //la capacité résiduelle de l'arc inverse est changée automatiquement, les négatifs sont tolérés
  void setResidualCapacity(Graph &graph,int newCap); //la capacité résiduelle de l'arc inverse est changée automatiquement
  Vertex &getStart(Graph &graph);
  Vertex &getEnd(Graph &graph);
  Edge &getPairedEdge(Graph &graph);
};

class Graph
{
public:
  // attributs
  int nbVertices;
  int nbEdges;
  std::vector<Vertex> vertices;
  std::vector<Edge> edges;
  int src;
  int sink;

  // méthodes
  Graph(int nbVertices, int nbEdges, int src, int sink, int edgeArray[][3]);
  Graph(int nbVertices, int nbEdges, int edgeArray[][5]);      // ancien constructeur
  Graph(int nbVertices);                                       // pour créer un graphe sans arêtes, utile lors de la création des graphes résiduels
  void print();
  void addVertex();
  void addEdge(Edge edge);
  Graph *getResidualGraph();                                   // ne pas oublier de faire appel à delete pour éviter les fuites mémoires, (en vrai c'est pas grave)
  void increaseFlow(int edgeId, int increase);                 // augmente le flot de l'arête edgeId, les négatifs sont tolérés
  void setFlow(int edgeId, int newFlow);                       // change le flot de l'arête edgeId
  Edge &getEnteringEdge(int vertexId, int edgeId);             // retourne la n-ième arête entrante du sommet m (m=vertexId,n=edgeId)
  Edge &getLeavingEdge(int vertexId, int edgeId);              // retourne la n-ième arête sortante du sommet m (m=vertexId,n=edgeId)
  Vertex &getEnteringNeighbour(int vertexId, int neighbourId); // retourne le n-ième voisin entrant du sommet m (m=vertexId,n=neighbourId)
  Vertex &getLeavingNeighbour(int vertexId, int neighbourId);  // retourne le n-ième voisin sortant du sommet m (m=vertexId,n=neighbourId)
  Vertex &getStart(int edgeId);                                // retourne le sommet de départ de l'arête n (n=edgeId)
  Vertex &getEnd(int edgeId);                                  // retourne le sommet de d'arrivée de l'arête n (n=edgeId)
  Edge &getPairedEdge(int edgeId);                             // retourne l'arc associé de l'arête n (n=edgeId)
};

#endif
