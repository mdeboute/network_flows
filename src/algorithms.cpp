#include <iostream>
#include "algorithms.hpp"
#include "Graph.hpp"
#include "checker.hpp"
#include <cstdio>
#include <limits.h>
#include <climits> // for INT_MAX
#include <queue>
#include <string.h>
#include <ctime>

// The main function that finds shortest distances from a node
// to all other vertices using Bellman-Ford algorithm. The
// function also detects negative weight cycle
int BellmanFord(Graph *graph, int pred[], int startingVrt, bool toVisit[])
{
    int V = graph->nbVertices;
    int E = graph->nbEdges;
    int dist[V];
    bool shouldVisit[V];

    for (int i = 0; i < V; i++)
    {
        shouldVisit[i] = toVisit[i];
    }

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[startingVrt] = 0;

    std::queue<int> queue;
    queue.push(startingVrt);
    int count[V];
    bool isInQueue[V];
    for (int i = 0; i < V; i++)
    {
        count[i] = 0;
        isInQueue[i] = false;
    }

    count[startingVrt]++;
    isInQueue[startingVrt] = true;

    while (queue.size() != 0)
    {
        int vertex = queue.front();
        isInQueue[vertex] = false;
        queue.pop();
        toVisit[vertex] = false;
        for (int id : graph->vertices[vertex].leavingEdgesId)
        {
            Edge e = graph->edges[id];
            if (graph->edges[id].residualCapacity == 0)
                continue;
            int vertex2 = graph->edges[id].endId;
            if (dist[vertex2] > dist[vertex] + graph->edges[id].cost)
            {
                dist[vertex2] = dist[vertex] + graph->edges[id].cost;
                pred[vertex2] = vertex;
                if (!isInQueue[vertex2] && shouldVisit[vertex2])
                {
                    queue.push(vertex2);
                    isInQueue[vertex2] = true;
                    count[vertex2]++;
                    if (count[vertex2] >= V)
                    {
                        // std::cout << "contains a negative cycle" << std::endl;
                        return vertex2;
                    }
                }
            }
        }
    }
    // std::cout << "!doesn't! contain a negative cycle" << std::endl;
    return -1;
}

int findTheTruth(bool toVisit[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (toVisit[i])
            return i;
    }
    return -1;
}

int findNegativeCycle(Graph *graph, int pred[])
{
    bool toVisit[graph->nbVertices];
    for (int i = 0; i < graph->nbVertices; i++)
    {
        toVisit[i] = true;
    }
    int u = graph->src;
    while (u != -1)
    {
        int probVertex = BellmanFord(graph, pred, u, toVisit);
        if (probVertex != -1)
            return probVertex;
        u = findTheTruth(toVisit, graph->nbVertices);
    }
    return -1;
}

// int findNegativeCycle(Graph *graph, int pred[])
// {
//     int V = graph->nbVertices;
//     int E = graph->nbEdges;
//     int dist[V];

//     for (int i = 0; i < V; i++)
//         dist[i] = INT_MAX;
//     dist[graph->src] = 0;

//     for (int i = 1; i < V ; i++)
//     {
//         for (int j = 0; j < E; j++)
//         {
//             if (graph->edges[j].residualCapacity == 0)
//                 continue;
//             int u = graph->edges[j].startId;
//             int v = graph->edges[j].endId;
//             int weight = graph->edges[j].cost;
//             if (dist[u] != INT_MAX && dist[u] + weight < dist[v]){
//                 dist[v] = dist[u] + weight;
//                 pred[v] = u;
//             }
//         }
//     }

//     // for(int i = 0; i < V; i++){
//     //     std::cout << pred[i];
//     // }
//     // std::cout << std::endl;

//     for (int i = 0; i < E; i++)
//     {
//         if (graph->edges[i].residualCapacity == 0)
//             continue;
//         int u = graph->edges[i].startId;
//         int v = graph->edges[i].endId;
//         int weight = graph->edges[i].cost;
//         if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
//         {
//             printf("Graph contains negative weight cycle!\n");
//             return u;
//         }
//     }

//     printf("Graph doesn't contain negative weight cycle!\n");
//     // graph->print();
//     return -1;
// }

int getNodeFromNegCycleInPath(Graph *graph, int pred[], int probVertex)
{
    bool tab[graph->nbVertices];
    for (int i = 0; i < graph->nbVertices; i++)
    {
        tab[i] = false;
    }
    while (!tab[probVertex])
    {
        tab[probVertex] = true;
        probVertex = pred[probVertex];
    }
    return probVertex;
}

int recFindCycle(Graph *graph, int pred[], long cost[], bool visited[], int precVrt, int currVrt){
    if(visited[currVrt]){
        pred[currVrt] = precVrt;
        return currVrt;
    }
    visited[currVrt] = true;
    for(int idEdge : graph->vertices[currVrt].leavingEdgesId){
        if(cost[idEdge] == 0){
            int result = recFindCycle(graph, pred, cost, visited, currVrt, graph->edges[idEdge].endId);
            if(result != -1){
                pred[currVrt] = precVrt;
                return result;
            }
        }
    }
    visited[currVrt] = false;
    return -1;
}

int findCycle(Graph *graph, int pred[], long cost[], int idVrt){
    bool visited[graph->nbVertices];
    for(int i = 0; i < graph->nbVertices; i++){
        visited[i] = false;
    }
    visited[idVrt] = true;
    for(int idEdge : graph->vertices[idVrt].leavingEdgesId){
        if(cost[idEdge] == 0){
            int result = recFindCycle(graph, pred, cost, visited, idVrt, graph->edges[idEdge].endId);
            if(result != -1){
                return result;
            }
        }
    }
    std::cout << "WOOPS" << std::endl;
    return -1;
}

int findMeanNegativeCycle(Graph* graph, int pred[]){
    int V = graph->nbVertices;
    int E = graph->nbEdges;
    long dist[V][V+1];
    long costMajoring = 0;  //edges with resCap = 0 have huge cost instead
    for(Edge e : graph->edges){
        if(e.cost > costMajoring){
            costMajoring = e.cost;
        }
    }
    costMajoring = costMajoring * V;

    for (int i = 0; i < V; i++)
        for(int j = 0; j < V+1; j++)
            dist[i][j] = INT_MAX;
    dist[graph->src][0] = 0;

    for (int i = 1; i < V + 1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            long weight;
            if (graph->edges[j].residualCapacity > 0)
                weight = graph->edges[j].cost;
            else{
                weight = costMajoring;
            }
            int u = graph->edges[j].startId;
            int v = graph->edges[j].endId;
            if (dist[u][i-1] != INT_MAX && dist[u][i-1] + weight < dist[v][i]){
                dist[v][i] = dist[u][i-1] + weight;
            }
        }
    }

    float alpha = INT_MAX;
    int bigNominator;
    int bigDenominator;
    for(int i = 0; i < V; i++){
        if(dist[i][V] == INT_MAX) continue;
        float maxValue = -INT_MAX;
        int nominator;
        int denominator;
        for(int j = 0; j < V; j++){
            if(dist[i][j] == INT_MAX) continue;
            if((dist[i][V] - dist[i][j]) > maxValue * (V - j)){
                maxValue = (dist[i][V] - dist[i][j]);
                maxValue = maxValue / (V - j);
                nominator = (dist[i][V] - dist[i][j]);
                denominator = (V - j);
            }
        }
        if(maxValue < alpha){
            alpha = maxValue;
            bigNominator = nominator;
            bigDenominator = denominator;
        }
    }
    if(bigNominator >= 0)
        return -1;

    long newCosts[E];
    for(int i = 0; i < E; i++){
        if(graph->edges[i].residualCapacity > 0)
            newCosts[i] = graph->edges[i].cost * bigDenominator - bigNominator;
         else
            newCosts[i] = costMajoring * bigDenominator - bigNominator;
    }

    for(int i = 0; i < V; i++){
        for(int j = 1; j < V + 1; j++){
            if(dist[i][j] != INT_MAX){
                dist[i][j] = dist[i][j] * bigDenominator - j * bigNominator;
            }
        }
    }

    float alpha1 = INT_MAX;
    for(int i = 0; i < V; i++){
        if(dist[i][V] == INT_MAX) continue;
        float maxValue = -INT_MAX;
        for(int j = 0; j < V; j++){
            if(dist[i][j] == INT_MAX) continue;
            if((dist[i][V] - dist[i][j]) > maxValue * (V - j)){
                maxValue = (dist[i][V] - dist[i][j]);
                maxValue = maxValue / (V - j);
            }
        }
        if(maxValue < alpha1){
            alpha1 = maxValue;
        }
    }

    long smallestDist[V];
    for(int i = 0; i < V; i++){
        long min = dist[i][0];
        for(int j = 1; j < V + 1; j++){
            if(dist[i][j] < min){
                min = dist[i][j];
            }
        }
        smallestDist[i] = min;
    }

    for(int i = 0; i < E; i++){
        if(graph->edges[i].residualCapacity > 0)
            newCosts[i] +=  smallestDist[graph->edges[i].startId] - smallestDist[graph->edges[i].endId];
    }

    // for (int i = 0; i < V; i++)
    //     for(int j = 0; j < V+1; j++)
    //         dist[i][j] = INT_MAX;
    // dist[graph->src][0] = 0;

    // for (int i = 1; i < V + 1; i++)
    // {
    //     for (int j = 0; j < E; j++)
    //     {
    //         long weight = newCosts[j];
    //         int u = graph->edges[j].startId;
    //         int v = graph->edges[j].endId;
    //         if (dist[u][i-1] != INT_MAX && dist[u][i-1] + weight < dist[v][i]){
    //             dist[v][i] = dist[u][i-1] + weight;
    //         }
    //     }
    // }


    // int idProbVertex = -1;
    // for(int i = 0; i < V; i++){
    //     if(dist[i][V] == INT_MAX) continue;
    //     long max = -INT_MAX;
    //     for(int j = 1; j < V; j++){
    //         if(dist[i][j] == INT_MAX) continue;
    //         if(dist[i][V] - dist[i][j] > max){
    //             int n = dist[i][V];
    //             int m = dist[i][j];
    //             max = dist[i][V] - dist[i][j];
    //         }
    //     }
    //     if(max == 0){
    //         idProbVertex = i;
    //         break;
    //     }
    // }
    for(int i = 0; i < V; i++){
        int a = findCycle(graph, pred, newCosts, i);
        if(a != -1)
            return a;
    }
    return -1;
}

void meanCycleCancelling(Graph *originGraph){
    originGraph->fromMultipleToOne();

    originGraph->removeLonelyNodes();

    Graph noParallelGraph(originGraph->nbVertices);

    originGraph->switchOffParallel(&noParallelGraph);

    shortestAugmentingPath(&noParallelGraph);

    originGraph->switchOnParallel(&noParallelGraph);
    std::cout << originGraph->getValueObjMinCost() << std::endl;

    Graph *graph = originGraph->getResidualGraph(false);

    int pred[graph->vertices.size()];
    int probVertex = findMeanNegativeCycle(graph, pred);

    while (probVertex != -1)
    {
        int initialVertex = probVertex;
        std::vector<int> edgesToChange;

        int idMinEdge = -1;
        for (int i = 0; i < graph->vertices[probVertex].enteringEdgesId.size(); i++)
        {
            int idStartVertex = graph->edges[graph->vertices[probVertex].enteringEdgesId[i]].startId;
            int resCapEdge = graph->edges[graph->vertices[probVertex].enteringEdgesId[i]].residualCapacity;
            int costEdge = graph->edges[graph->vertices[probVertex].enteringEdgesId[i]].cost;
            if (idStartVertex == pred[probVertex] && resCapEdge != 0 && (costEdge < graph->edges[idMinEdge].cost || idMinEdge == -1))
            {
                idMinEdge = graph->vertices[probVertex].enteringEdgesId[i];
            }
        }
        if (idMinEdge == -1)
        {
            std::cout << "ERROR, IDMINEDGE STILL -1" << std::endl;
        }
        edgesToChange.push_back(idMinEdge);
        int minResCap = graph->edges[idMinEdge].residualCapacity;
        probVertex = pred[probVertex];

        while (probVertex != initialVertex)
        {
            int idMinEdge = -1;
            for (int i = 0; i < graph->vertices[probVertex].enteringEdgesId.size(); i++)
            {
                int idStartVertex = graph->edges[graph->vertices[probVertex].enteringEdgesId[i]].startId;
                int resCapEdge = graph->edges[graph->vertices[probVertex].enteringEdgesId[i]].residualCapacity;
                int costEdge = graph->edges[graph->vertices[probVertex].enteringEdgesId[i]].cost;
                if (idStartVertex == pred[probVertex] && resCapEdge != 0 && (costEdge < graph->edges[idMinEdge].cost || idMinEdge == -1))
                {
                    idMinEdge = graph->vertices[probVertex].enteringEdgesId[i];
                }
            }
            if (idMinEdge == -1)
            {
                std::cout << "ERROR, IDMINEDGE STILL -1" << std::endl;
            }
            if (graph->edges[idMinEdge].residualCapacity < minResCap)
            {
                minResCap = graph->edges[idMinEdge].residualCapacity;
            }
            edgesToChange.push_back(idMinEdge);
            probVertex = pred[probVertex];
        }

        for (int i = 0; i < edgesToChange.size(); i++)
        {
            Edge e = graph->edges[edgesToChange[i]];

            graph->edges[edgesToChange[i]].increaseResidualCapacity(*graph, -minResCap);
        }
        originGraph->fillGraphFromResidual(graph);
        std::cout << originGraph->getValueObjMinCost() << std::endl;
        probVertex = findMeanNegativeCycle(graph, pred);
    }
    originGraph->fillGraphFromResidual(graph);
}

void cycleCancelling(Graph *originGraph)
{
    originGraph->fromMultipleToOne();

    originGraph->removeLonelyNodes();

    Graph noParallelGraph(originGraph->nbVertices);

    originGraph->switchOffParallel(&noParallelGraph);

    shortestAugmentingPath(&noParallelGraph);

    originGraph->switchOnParallel(&noParallelGraph);

    // std::cout << "obj : " << originGraph->getValueObjMinCost() << std::endl;

    Graph *graph = originGraph->getResidualGraph(false);

    int pred[graph->vertices.size()];
    int probVertex = findNegativeCycle(graph, pred);

    if (probVertex != -1)
    {
        probVertex = getNodeFromNegCycleInPath(graph, pred, probVertex);
    }

    while (probVertex != -1)
    {
        int initialVertex = probVertex;
        std::vector<int> edgesToChange;

        int idMinEdge = -1;
        for (int i = 0; i < graph->vertices[probVertex].enteringEdgesId.size(); i++)
        {
            int idStartVertex = graph->edges[graph->vertices[probVertex].enteringEdgesId[i]].startId;
            int resCapEdge = graph->edges[graph->vertices[probVertex].enteringEdgesId[i]].residualCapacity;
            int costEdge = graph->edges[graph->vertices[probVertex].enteringEdgesId[i]].cost;
            if (idStartVertex == pred[probVertex] && resCapEdge != 0 && (idMinEdge == -1 || costEdge < graph->edges[idMinEdge].cost))
            {
                idMinEdge = graph->vertices[probVertex].enteringEdgesId[i];
            }
        }
        if (idMinEdge == -1)
        {
            std::cout << "ERROR, IDMINEDGE STILL -1" << std::endl;
        }
        edgesToChange.push_back(idMinEdge);
        int minResCap = graph->edges[idMinEdge].residualCapacity;
        probVertex = pred[probVertex];

        while (probVertex != initialVertex)
        {
            int idMinEdge = -1;
            for (int i = 0; i < graph->vertices[probVertex].enteringEdgesId.size(); i++)
            {
                int idStartVertex = graph->edges[graph->vertices[probVertex].enteringEdgesId[i]].startId;
                int resCapEdge = graph->edges[graph->vertices[probVertex].enteringEdgesId[i]].residualCapacity;
                int costEdge = graph->edges[graph->vertices[probVertex].enteringEdgesId[i]].cost;
                if (idStartVertex == pred[probVertex] && resCapEdge != 0 && ( idMinEdge == -1  || costEdge < graph->edges[idMinEdge].cost))
                {
                    idMinEdge = graph->vertices[probVertex].enteringEdgesId[i];
                }
            }
            if (idMinEdge == -1)
            {
                std::cout << "ERROR, IDMINEDGE STILL -1" << std::endl;
            }
            if (graph->edges[idMinEdge].residualCapacity < minResCap)
            {
                minResCap = graph->edges[idMinEdge].residualCapacity;
            }
            edgesToChange.push_back(idMinEdge);
            probVertex = pred[probVertex];
        }

        for (int i = 0; i < edgesToChange.size(); i++)
        {
            Edge e = graph->edges[edgesToChange[i]];

            graph->edges[edgesToChange[i]].increaseResidualCapacity(*graph, -minResCap);
        }

        probVertex = findNegativeCycle(graph, pred);
        if (probVertex != -1)
        {
            probVertex = getNodeFromNegCycleInPath(graph, pred, probVertex);
        }
    }
    originGraph->fillGraphFromResidual(graph);
    // std::cout << validFlow(originGraph) << std::endl;
}

void retreat(Graph *graph, int i, int dist[])
{
    int min = INT_MAX;
    for (int j = 0; j < graph->vertices[i].leavingEdgesId.size(); j++)
    {
        if (graph->edges[graph->vertices[i].leavingEdgesId[j]].residualCapacity > 0 && min > dist[graph->vertices[i].getLeavingNeighbour(*graph, j).id] + 1)
        {
            min = dist[graph->vertices[i].getLeavingNeighbour(*graph, j).id] + 1;
        }
    }
    dist[i] = min;
}

void augment(Graph *graph, int pred[])
{
    int vertexId = graph->sink;
    int min = graph->getEdgeFromVerticesId(pred[vertexId], vertexId).residualCapacity;
    while (vertexId != graph->src)
    {
        if (min > graph->getEdgeFromVerticesId(pred[vertexId], vertexId).residualCapacity)
        {
            min = graph->getEdgeFromVerticesId(pred[vertexId], vertexId).residualCapacity;
        }
        vertexId = pred[vertexId];
    }
    vertexId = graph->sink;
    while (vertexId != graph->src)
    {
        graph->getEdgeFromVerticesId(vertexId, pred[vertexId]).increaseResidualCapacity(*graph, min);
        vertexId = pred[vertexId];
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void distanceLabelling(Graph *graph, int dist[])
{
    bool marks[graph->nbVertices];
    for (int i = 0; i < graph->nbVertices; i++)
    {
        marks[i] = false;
        dist[i] = -1;
    }
    marks[graph->sink] = true;
    dist[graph->sink] = 0;
    std::queue<int> List;
    List.push(graph->sink);
    while (List.size() > 0)
    {
        bool hasAdmissibleArc = false;
        for (int i = 0; i < graph->vertices[List.front()].leavingEdgesId.size(); i++)
        {
            if (marks[graph->edges[graph->vertices[List.front()].leavingEdgesId[i]].endId] == false)
            {
                hasAdmissibleArc = true;
                marks[graph->edges[graph->vertices[List.front()].leavingEdgesId[i]].endId] = true;
                dist[graph->edges[graph->vertices[List.front()].leavingEdgesId[i]].endId] = dist[List.front()] + 1;
                List.push(graph->edges[graph->vertices[List.front()].leavingEdgesId[i]].endId);
            }
        }
        List.pop();
    }
    return;
}

void shortestAugmentingPath(Graph *originGraph)
{

    originGraph->removeLonelyNodes();

    Graph *graph = originGraph->getResidualGraph(true);
    int dist[graph->nbVertices];
    distanceLabelling(graph, dist);
    int pred[graph->nbVertices];
    for (int i = 0; i < graph->nbVertices; i++)
    {
        pred[i] = -1;
    }

    int i = graph->src;
    while (dist[graph->src] < graph->nbVertices)
    {
        bool hasAdmissibleArc = false;
        for (int p = 0; p < graph->vertices[i].leavingEdgesId.size(); p++)
        {
            int j = graph->edges[graph->vertices[i].leavingEdgesId[graph->vertices[i].height]].endId;
            graph->vertices[i].height += 1;
            if (graph->vertices[i].height == graph->vertices[i].nbLeavingEdges)
                graph->vertices[i].height = 0;
            if (graph->getEdgeFromVerticesId(i, j).residualCapacity > 0 && dist[i] == dist[j] + 1)
            {
                hasAdmissibleArc = true;
                pred[j] = i; // advance(i) cf. pdf
                i = j;
                if (i == graph->sink)
                {
                    augment(graph, pred);
                    i = graph->src;
                }
                break;
            }
        }

        if (hasAdmissibleArc == false)
        {
            retreat(graph, i, dist);
            if (i != graph->src)
            {
                i = pred[i];
            }
        }
    }
    originGraph->fillGraphFromResidual(graph);
}

void distanceLabelling(Graph *graph)
{
    bool marks[graph->nbVertices];
    for (int i = 0; i < graph->nbVertices; i++)
    {
        marks[i] = false;
        graph->vertices[i].height = -1;
    }
    marks[graph->sink] = true;
    graph->vertices[graph->sink].height = 0;
    std::queue<int> List;
    List.push(graph->sink);
    while (List.size() > 0)
    {
        bool hasAdmissibleArc = false;
        for (int i = 0; i < graph->vertices[List.front()].enteringEdgesId.size(); i++)
        {
            if (marks[graph->edges[graph->vertices[List.front()].enteringEdgesId[i]].startId] == false)
            {
                hasAdmissibleArc = true;
                marks[graph->edges[graph->vertices[List.front()].enteringEdgesId[i]].startId] = true;
                graph->vertices[graph->edges[graph->vertices[List.front()].enteringEdgesId[i]].startId].height = graph->vertices[List.front()].height + 1;
                List.push(graph->edges[graph->vertices[List.front()].enteringEdgesId[i]].startId);
            }
        }
        List.pop();
    }
    graph->vertices[graph->src].height = graph->vertices[graph->src].height * 2;
    return;
}

void preflowPush(Graph *original_graph)
{
    // distance
    distanceLabelling(original_graph);

    Graph *graph = original_graph->getResidualGraph(true);
    std::queue<int> activeNodes;

    // Initialisation des valeurs
    for (int i = 0; i < graph->nbVertices; ++i)
    {
        graph->vertices[i].exceedingFlow = 0;
    }

    for (int id : graph->vertices[graph->src].leavingEdgesId)
    {
        graph->vertices[graph->edges[id].endId].exceedingFlow = graph->edges[id].residualCapacity;
        graph->edges[id].increaseResidualCapacity(*graph, -graph->vertices[graph->edges[id].endId].exceedingFlow);
        activeNodes.push(graph->edges[id].endId);
    }

    // Tant qu'il existe du flot en exces
    while (!activeNodes.empty())
    {
        int v = activeNodes.front();
        bool admissibleEdge = false;
        for (int id : graph->vertices[v].leavingEdgesId)
        {
            if (graph->edges[id].residualCapacity > 0 && graph->vertices[graph->edges[id].endId].height + 1 == graph->vertices[v].height)
            {
                admissibleEdge = true;
                int delta = std::min(graph->vertices[v].exceedingFlow, graph->edges[id].residualCapacity);
                graph->edges[id].increaseResidualCapacity(*graph, -delta);
                graph->vertices[v].exceedingFlow -= delta;
                if (graph->edges[id].endId != graph->src && graph->edges[id].endId != graph->sink && graph->vertices[graph->edges[id].endId].exceedingFlow == 0)
                {
                    activeNodes.push(graph->edges[id].endId);
                }
                graph->vertices[graph->edges[id].endId].exceedingFlow += delta;
                if (graph->vertices[v].exceedingFlow == 0)
                {
                    activeNodes.pop();
                    break;
                }
            }
        }
        if (!admissibleEdge)
        {
            int min_height = 2 * graph->nbVertices;
            for (int id : graph->vertices[v].leavingEdgesId)
            {
                if (graph->edges[id].residualCapacity > 0 && graph->vertices[graph->edges[id].endId].height + 1 < min_height)
                {
                    min_height = graph->vertices[graph->edges[id].endId].height + 1;
                }
            }
            graph->vertices[v].height = min_height;
        }
    }
    original_graph->fillGraphFromResidual(graph);
    std::cout << graph->vertices[graph->sink].exceedingFlow << std::endl;
}
