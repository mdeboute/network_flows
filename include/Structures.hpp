#include <vector>
#ifndef structs
#define structs



class Edge;
class Graph;

class Vertex
{
  public:
    int id;
    int nbEnteringEdges;
    int nbLeavingEdges;
    std::vector<int> enteringEdgesId;
    std::vector<int> leavingEdgesId;

    Vertex(int id);
    void print();
    Edge& getEnteringEdge(Graph& graph,int id); //retourne la n-ième arête entrante (n=id)
    Edge& getLeavingEdge(Graph& graph,int id); //retourne la n-ième arête sortante (n=id)
    Vertex& getEnteringNeighbour(Graph& graph,int id); //retourne le n-ième voisin entrant (n=id)
    Vertex& getLeavingNeighbour(Graph& graph,int id); //retourne le n-ième voisin sortant (n=id)
};



class Edge
{
  public:
    int id;
    int cost;
    int minCapacity;
    int maxCapacity;
    int flow;
    int startId;
    int endId;
    int pairedEdgeId;

    Edge(int id,int cost,int minCapacity,int maxCapacity,int startId,int endId);
    void print();
    void increaseFlow(Graph& pairedGraph,int increase); //les négatifs sont tolérés, pairedGraph est le graphe asscocié
    void setFlow(Graph& pairedGraph,int newFlow); //pairedGraph est le graphe asscocié
    Vertex& getStart(Graph& graph);
    Vertex& getEnd(Graph& graph);
    Edge& getPairedEdge(Graph& pairedGraph); //pairedGraph est le graphe asscocié
};



class Graph
{
  public:
    static const int edgeInfoAmount = 5;
    int nbVertices;
    int nbEdges;
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
    Graph* pairedGraph;

    Graph(int nbVertices,int nbEdges,int edgeArray[][edgeInfoAmount]);
    Graph(int nbVertices); //pour créer un graphe sans arêtes, utile lors de la création des graphes résiduels
    void print();
    void printPairings(); //à  implémenter
    void addVertex();
    void addEdge(Edge edge);
    Graph* getResidualGraph();
};



#endif
