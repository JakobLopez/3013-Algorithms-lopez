//AVLtree.h
//This file declares a struct node and class AVL. Public and private methods
//are established, so that the .cpp file can define them.
#pragma once

#include <iostream>
#include <fstream>
#include <time.h>
#include <string>

using namespace std;

struct AVLnode {
	string value;
	AVLnode *left;
	AVLnode *right;
	AVLnode *parent;
	int avlValue;
	AVLnode(string word);
};

class AVL {

private:
	AVLnode *root;
	int comparisons;

	//truee if right heavy
	bool rightHeavy(AVLnode *);

	//true if left heavy
	bool leftHeavy(AVLnode *);

	//inserts node in tree
	void insert(AVLnode *&, AVLnode *&);

	//inorder traversal
	void inorder(AVLnode *);

	//preorder traversal
	void preorder(AVLnode *);

	//postorder traversal
	void postorder(AVLnode *);

	//Removes node from tree
	AVLnode* remove(AVLnode*&, string);

	//Returns either predecessor or successor
	AVLnode* predSuccessor(AVLnode*);

	//Prints node
	void printAVLnode(AVLnode *, string);

	//Returns height of tree
	int  height(AVLnode *);

	//Compute all nodes' avl values
	void computeAvlValues(AVLnode *&);

	//Rotates tree left
	void rotateLeft(AVLnode *&);

	//Rotates tree right
	void rotateRight(AVLnode *&);

	//Returns avl value
	int  avlValue(AVLnode *);

public:
	//Default constructor
	AVL();

	//Destructor
	~AVL();

	//Calls dumpTree
	void doDumpTree(AVLnode *);
	void dumpTree() {
		cout << "---------------------------------" << endl;
		cout << "Root:   " << root << "\n";
		doDumpTree(root);
	};

	//Inserts node
	void insert(string);

	//Calls private inorder traversal
	void showInorder() { inorder(root); };

	//Calls private preorder traversal
	void showPreorder() { preorder(root); };

	//Calls private postorder traversal
	void showPostorder() { postorder(root); };

	//Returns true if node found
	bool search(string);

	//Removes node
	void remove(string word) { root = remove(root, word); };

	//Returns tree height
	int  treeHeight();
	void graphVizGetIds(AVLnode *, ofstream &);
	void graphVizMakeConnections(AVLnode *, ofstream &);
	void graphVizOut(string);

	//returns number of comparisons
	int totalComparisons();
};
