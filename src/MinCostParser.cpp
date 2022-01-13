#include "Structures.hpp"
#include <fstream>
#include <sstream>
using namespace std;

void openFile(ifstream&, string);
void processFile(ifstream&);

// this function parse an input file and return a network graph
// parameters: filepath
// return value: graph
Graph parse(std::string filePath)
{
    ifstream file;
    openFile(file, filePath);
    Graph graph processFile(file);
    file.close();
    return graph;
}

void openFile(ifstream& file, string filePath)
{
    file.open(filePath);
    if (file.is_open())
    {
        cout << "File opened successfully" << endl;
    }
    else
    {
        cerr << "File open failed" << endl;
        exit(-1);
    }
}

Graph processFile(ifstream& file)
{
    // data format example:
    // "c 20 msec" comment line, to skip
    // "p min 49 520" problem line where the first number is the number of nodes and the second number is the number of edges
    // "n 47 -769230" nodes line, the first number is the node id, the second number is the node flow
    // "a 1 5 0 769230 1132" edge line, the first number is the source node id, the second number is the destination node id,
    // the third number is the minimum flow capacity, the fourth number is the maximum flow capacity,
    // the fifth number is the cost of the edge

    string line;
    int nbNodes, nbEdges;
    int nodeId, nodeFlow;
    int sourceNodeId, destinationNodeId, minFlow, maxFlow, cost;

    //for all the line of the file parse the line and store the data to create the graph
    while (getline(file, line))
    {
        if (line[0] == 'c')
        {
            // comment line, skip
        }
        else if (line[0] == 'p')
        {
            // problem line, get the number of nodes and the number of edges
            stringstream ss(line);
            string token;
            getline(ss, token, ' ');
            getline(ss, token, ' ');
            nbNodes = stoi(token);
            getline(ss, token, ' ');
            nbEdges = stoi(token);
        }
        else if (line[0] == 'n')
        {
            // nodes line, get the node id and the node flow
            stringstream ss(line);
            string token;
            getline(ss, token, ' ');
            getline(ss, token, ' ');
            nodeId = stoi(token);
            getline(ss, token, ' ');
            nodeFlow = stoi(token);
        }
        else if (line[0] == 'a')
        {
            // edge line, get the source node id, the destination node id, the minimum flow capacity, the maximum flow capacity,
            // the cost of the edge
            stringstream ss(line);
            string token;
            getline(ss, token, ' ');
            getline(ss, token, ' ');
            sourceNodeId = stoi(token);
            getline(ss, token, ' ');
            destinationNodeId = stoi(token);
            getline(ss, token, ' ');
            minFlow = stoi(token);
            getline(ss, token, ' ');
            maxFlow = stoi(token);
            getline(ss, token, ' ');
            cost = stoi(token);
        }
    }
    // create the graph
    int edgeArray[nbEdges][5] = {
        {sourceNodeId, destinationNodeId, minFlow, maxFlow, cost}};
}
