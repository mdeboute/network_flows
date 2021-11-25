#ifndef GRAPH_H
#define GRAPH_H


//stores adjacency list items
struct AdjListNode
{
    int val;
    int cost;
    AdjListNode* next;
};

//structure to store edges
struct Edge
{
    int start_ver, end_ver, weight;
};

class Graph
{
    private:
    // insert new nodes into adjacency list from given graph
    AdjListNode* getAdjListNode(int value, int weight, AdjListNode* head)
    {
    AdjListNode* newNode = new AdjListNode;
    newNode->val = value;
    newNode->cost = weight;
    newNode->next = head;
    return newNode;
    }
    // number of nodes in the graph
    int N;

    public:
    AdjListNode **head;
    //Constructor
    Graph(Edge edges[], int n, int N);
    //Destructor
    ~Graph();
    void printAdjList(AdjListNode* ptr, int i);
    //To print the graph
    void printGraph();
};
