#include <iostream>
#include "Graph.cpp"

using namespace std;


int main()
{
	// graph edges array.
    Edge edges[] = {
        // (x, y, w) -> edge from x to y with weight w
        {0,1,2},{0,2,4},{1,4,3},{2,3,2},{3,1,4},{4,3,3}
    };
    // number of vertices in the graph
    int N = 5;
    // calculate number of edges
    int n = sizeof(edges)/sizeof(edges[0]);
    // construct graph
    Graph Graph(edges, n, N);
    // print adjacency list representation of graph
    Graph.printGraph();
    return 0;
}