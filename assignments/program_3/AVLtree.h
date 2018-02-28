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
	bool rightHeavy(AVLnode *);
	bool leftHeavy(AVLnode *);
	void insert(AVLnode *&, AVLnode *&);
	void inorder(AVLnode *);
	void preorder(AVLnode *);
	void postorder(AVLnode *);
	AVLnode* remove(AVLnode*&, string);
	AVLnode* predSuccessor(AVLnode*);
	void printAVLnode(AVLnode *, string);
	int  height(AVLnode *);
	void computeAvlValues(AVLnode *&);
	void rotateLeft(AVLnode *&);
	void rotateRight(AVLnode *&);
	int  avlValue(AVLnode *);

public:
	AVL();
	~AVL();
	void doDumpTree(AVLnode *);
	void dumpTree() {
		cout << "---------------------------------" << endl;
		cout << "Root:   " << root << "\n";
		doDumpTree(root);
	};
	void insert(string);
	void showInorder() { inorder(root); };
	void showPreorder() { preorder(root); };
	void showPostorder() { postorder(root); };
	bool search(string);
	void remove(string word) { root = remove(root, word); };
	int  treeHeight();
	void graphVizGetIds(AVLnode *, ofstream &);
	void graphVizMakeConnections(AVLnode *, ofstream &);
	void graphVizOut(string);
};
