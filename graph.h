//
//  graph.h
//  Project4
//
//  Created by Bein, Doina on 4/21/18.
//  Copyright © 2018 Bein, Doina. All rights reserved.
//

#ifndef Graph_h
#define Graph_h

#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
using namespace std;

const int MAX_NODE_COUNT = 100;

class Graph 
{
 public:
	Graph(); // default constructor
	Graph(int rno, float rbudget); // constructor with two arguments representing the number of nodes, initial budget
	void addEdge(int x, int y); // adds an edge between two nodes in the graph node1 and node2
	void setValue(int node, float rval); // sets a value for a node
	void setBudget(float rbu); // sets the initial budget
	int getNSize(); // return number of nodes
	int getESize(); // return number of edges
	float getBudget(); // return current budget
	float getValue(int node) ; // returns the value of the node
	void readData (string fileName); // reads data from a specified file
	int DFS(int startNode); //return the number of nodes visited using BFS starting at startNode and accumulating values at each node, as long as the budget remains positive

	// return the starting node that gives a longest DFS run before running out of budget
	// if there are multiple nodes with the same DFS run length, return the smallest node
	int bestStartVertex();

 private:
	// member variables and helper functions (if needed)

	// Holds boolean values to indicate if an edge exit or not between any two nodes
	bool adjEdges[MAX_NODE_COUNT][MAX_NODE_COUNT] = { {false} };

	// Total number of edges in a graph 
	int numofNodes;

	// Total number of edges in a graph 
	int edge_size;

	// Total  budget amount for the game
	float budget;

	// Holds a collection value for each node in a graph  
	float chkPointValArry[MAX_NODE_COUNT] = {0.0};

    // Returns True when two nodes (x and y) are connected
	bool isConnected(int x, int y);
};

#endif /* Graph_h */
