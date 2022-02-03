#include "Structures.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;


Graph process(ifstream& file);
void open(ifstream& file, string filePath);

void open(ifstream& file, string filePath)
{
    file.open(filePath);
    if (file.is_open())
    {
        cout << "File opened successfully" << endl;
    }
    else
    {
        cerr << "File open failed\n" << endl;
        exit(-1);
    }
}

// this function parse an input file and return a network graph
// parameters: filepath
// return value: graph
Graph maxFlowParser(string filePath)
{
    ifstream file;
    open(file, filePath);
    Graph graph = process(file);
    file.close();
    return graph;
}

Graph process(ifstream& file)
{
    // data format example:
    // c Random Network, comment line to skip
    // p max    10      70, problem line, max flow, number of nodes, number of edges
    // n         1  s, node line, node number, node name (s for source)
    // n        10  t, node line, node number, node name (t for sink)
    // a       1       5    6694, edge line, from node, to node, the maximum flow capacity

    string line;
    int nbNodes, nbEdges;
    int sourceNodeId, destinationNodeId, maxFlow;
    vector<vector<int>> edgesArray;
    const char delimiter = ' ';

    auto isEmptyOrBlank = [](const std::string &s) {
        return s.find_first_not_of(" \t") == std::string::npos;
    };

    // for all the line of the file parse the line and store the data to create the graph
    while (getline(file, line))
    {
        if(file.eof()) break;

        if (line[0] == 'c')
        {
            // comment line, skip
        }
        else if (line[0] == 'p')
        {
            // problem line, get the number of nodes and the number of edges

            //Define the dynamic array variable of strings
            vector<string> outputArray;
            //Construct a stream from the string
            stringstream streamData(line);
            /*
            Declare string variable that will be used
            to store data after split
            */
            string val;
            /*
            The loop will iterate the splitted data and
            insert the data into the array
            */
            while (getline(streamData, val, delimiter)) {
                outputArray.push_back(val);
            }

            outputArray.erase(std::remove_if(outputArray.begin(), outputArray.end(), isEmptyOrBlank), outputArray.end());

            nbNodes = stoi(outputArray[2]);
            nbEdges = stoi(outputArray[3]);

        }
        else if (line[0] == 'n')
        {
            // skip
        }
        else if (line[0] == 'a')
        {
            // edge line, get the source node id, the destination node id, the maximum flow capacity
            vector<string> outputArray;
            stringstream streamData(line);
            string val;
            while (getline(streamData, val, delimiter)) {
                outputArray.push_back(val);
            }
            outputArray.erase(std::remove_if(outputArray.begin(), outputArray.end(), isEmptyOrBlank), outputArray.end());

            sourceNodeId = stoi(outputArray[1]);
            destinationNodeId = stoi(outputArray[2]);
            maxFlow = stoi(outputArray[3]);

            vector<int> edges{0, 0, maxFlow, sourceNodeId, destinationNodeId};
            edgesArray.push_back(edges);
        }
    }

    // convert the vector to an array
    int infos[nbEdges][5];
    for (int i = 0; i < nbEdges; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            infos[i][j] = edgesArray[i][j];
        }
    }

    // create the graph
    Graph graph(nbNodes, nbEdges, infos);

    cout << "Graph created!\n" << endl;

    return graph;
}
