//
//  graph.cpp
//  Project4
//
//  Created by Sheth, Sahil on 5/5/18.
//
//

#include "graph.h"

// A default constructor
Graph::Graph()
{
    numofNodes = 0;
    budget = 0.0;
    edge_size = 0;
}

// A parametrized constructor that takes number of nodes in a graph and budget
Graph::Graph(int rno, float rbudget)
{
    numofNodes = rno;
    budget = rbudget;
    edge_size = 0;
}

// This method adds an edge between two nodes (x and y) in the graph
void Graph::addEdge(int x, int y)
{
    if (adjEdges[x][y] == false)
    {
      edge_size++;
    }
    adjEdges[x][y]= true;
    adjEdges[y][x]= true;
}

// This method sets a value for a node
void Graph::setValue(int node, float rval)
{
    chkPointValArry[node] = rval;
}

// This method sets the initial budget
void Graph::setBudget(float rbu)
{
    budget = rbu;
}

// this method returns a number of nodes
int Graph::getNSize()
{
    return numofNodes;
}

// This method returns number of edges
int Graph::getESize()
{
    return edge_size;
}

// This method returns the current budget
float Graph::getBudget()
{
    return budget;
}

// This method returns True when two nodes (x and y) are connected
bool Graph::isConnected(int x, int y)
{
    return (adjEdges[x][y] == true);
}

float Graph::getValue(int node)
{
    return chkPointValArry[node];
}

// This method reads data from input file loads it into an array
void Graph::readData (string fileName)
{
    ifstream infile;
    int i, j;

    infile.open(fileName.c_str());

    // if input file is open
    if (infile.is_open())
    {
        infile >> numofNodes;
        infile >> budget;

        //cout << "readData(): numofNodes=" << numofNodes << "\tbudget=" << budget << endl;

        for (int idx = 0; idx < numofNodes; ++idx)
        {
            infile >> chkPointValArry[idx];

            //cout << "readData(): chkPointValArry[" << idx << "]=" <<  chkPointValArry[idx] << endl;
        }

        // Loading edges until EOF is reached

        while (1)
        {
            infile >> i;
            infile >> j;
            if(!infile.good())
            {
              break;
            }
            addEdge(i, j);

            //cout<< "edge_size= " << edge_size<<endl;
           //cout << "adjEdges[" << i << "]" << "[" << j << "]=" << endl;//<< adjEdges[i][j] << endl;
            //cout << "adjEdges[" << j << "]" << "[" << i << "]=" << adjEdges[j][i] << endl;
        }


        infile.close();
    }
    else
    {
        cout << "Failed to read input file " << fileName<< endl;
    }
}

// This method returns the starting node that gives a longest
// DFS run before running out of budget. If there are multiple
// nodes with the same DFS run length, then it returns the smallest node.
int Graph::bestStartVertex()
{
    int testDFSLen = 0;
    int bestDFSLen = 0;
    int bestStartNode = -1;

    for (int i = 0; i < numofNodes; i++)
    {
        testDFSLen = DFS(i);

        //cout <<  "bestStartVertex: DFS(" << i << ") Traversed node count = " << testDFSLen << endl;

        if (testDFSLen > bestDFSLen)
        {
            bestDFSLen = testDFSLen;
            bestStartNode = i;
        }
        else if (testDFSLen == bestDFSLen)
        {
            if (bestStartNode < 0)
            {
                bestStartNode = i;
            }
        }
    }

    //cout <<  "bestStartVertex: The best starting vertex is " << bestStartNode<< endl;

    return bestStartNode;
}

// This method returns the number of nodes visited using DFS starting
// at startNode and accumulating values at each node, as long as the
// budget remains positive
int Graph::DFS(int startNode)
{
    
    int dfsLen = 0;
    float balance = getBudget();
    std::stack<int> stak;
    bool visited[MAX_NODE_COUNT] = {false};

    stak.push(startNode);

    while (!stak.empty())
    {
        int k = stak.top();
        stak.pop();

        if (!visited[k])
        {
            visited[k] = true;

            if (balance > 0)
            {
                ++dfsLen;
                balance = balance + chkPointValArry[k];
            }

            if (balance <= 0)
            {
                break;
            }

            for (int i = numofNodes - 1; i >= 0; --i)
            {
                if (isConnected(k, i))
                {
                    stak.push(i);
                }
            }
        }
    }

    return dfsLen;
}
