#include <vector>
#ifndef structs
#define structs



class Edge;

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
    void setFlow(int newFlow); //à  implémenter
    void increaseFlow(int increase); //à  implémenter
};



class Graph
{
  public:
    static const int edgeInfoAmount = 5;
    int nbVertices;
    int nbEdges;
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;

    Graph(int nbVertices,int nbEdges,int edgeArray[][edgeInfoAmount]);
    Graph(int nbVertices); //pour créer un graphe sans arêtes, utile lors de la création des graphes résiduels
    void print();
    void addVertex(); //à  implémenter
    void addEdge(Edge edge);
    Graph* getResidualGraph();
};



#endif
