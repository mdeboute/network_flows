#include <iostream>
#include <ostream>
#include "Graph.hpp"

using namespace std;


void display_AdjList(AdjListNode* ptr, int i)
{
    while (ptr != nullptr) {
        cout << "(" << i << ", " << ptr->val
            << ", " << ptr->cost << ") ";
        ptr = ptr->next;
    }
    cout << endl;
}

Graph::Graph(Edge edges[], int n, int N)
{
    head = new AdjListNode*[N]();
    this->N = N;
    // initialize head pointer for all vertices
    for (int i = 0; i < N; ++i)
        head[i] = nullptr;
    // construct directed graph by adding edges to it
    for (unsigned i = 0; i < n; i++)  {
        int start_ver = edges[i].start_ver;
        int end_ver = edges[i].end_ver;
        int weight = edges[i].weight;
        // insert in the beginning
        AdjListNode* newNode = getAdjListNode(end_ver, weight, head[start_ver]);
        // point head pointer to new node
        head[start_ver] = newNode;
    }
}

 Graph::~Graph()
{
    for (int i = 0; i < N; i++){
        delete[] head[i];
        delete[] head;
    }
}
