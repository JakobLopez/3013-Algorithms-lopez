//BSTree.h
//This file declares a struct and class. Public and private methods
//are established, so that the .cpp file can define them.

#pragma once
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct node
{
	int data;
	node *left;
	node *right;
	node();
	node(int x);
};

class BSTree
{
private:
	node *root;

	//Counts number of nodes
	int count(node *root);

	//Inserts node into tree
	void insert(node *&root, node *&temp);

	//Prints node and childrens data,label and address
	void print_node(node *n, string label);

	//Returns the successor or predecessor
	node *minValueNode(node *root);

	//Deletes node from tree
	node *deleteNode(node *&root, int key);

	//Returns height of tree
	int height(node *root);

	// Print nodes at a given level 
	void printGivenLevel(node *root, int level);

	// Prints out all the unique node id's by traversing the tree.
	// Receivies a node pointer to root and performs a simple recursive
	// tree traversal.
	void GraphVizGetIds(node *nodePtr, ofstream &VizOut);

	// This method is partnered with the above method, but on this pass it
	// writes out the actual data from each node.
	void GraphVizMakeConnections(node *nodePtr, ofstream &VizOut);

public:
	//Default constructor
	BSTree();

	//Destructor
	~BSTree();

	//Returns number of nodes
	int count();

	//Inserts node into trww
	void insert(int x);

	//Calls private method to delete node
	void deleteNode(int key);

	//Calls private method to return either the successor or predecessor
	void minValue();

	//Calls private method and returns height of tree
	int height(int key);

	//Returns data of root node
	int top();

	//Line by line print level order traversal a tree
	void printLevelOrder();

	//Calls other two graphviz methods to create a data file
	// that can be used to visualize your expression tree.
	void GraphVizOut(string filename);
};
