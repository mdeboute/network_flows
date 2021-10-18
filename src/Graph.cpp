#include <iostream>
#include <ostream>
#include "Graph.hpp"

using namespace std;

template <typename V>
struct Vertex
{
    V *data;
    int index;

    Vertex();
    Vertex const Vertex &v);
    Vertex(const V &value, int index);
    ~Vertex();
    Vertex operator=(const Vertex &v);
};

template <typename E>
struct Edge
{
    E *data;
    int V1_index;
    int V2_index;

    Edge();
    Edge(const Edge &e);
    Edge(const E &value, int indV1_index, int V2_index);
    ~Edge();
    Edge operator=(const Edge &e);
};

template <typename V>
Vertex<V>::Vertex() : data(NULL), index(-1);
