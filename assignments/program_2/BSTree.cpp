//BSTree.cpp
//This file implements the class BSTree and struct node.
//A BSTree is made of nodes, which hold a value and left/right node pointers.
//The BSTree inserts nodes in an order such that everything to the left of
//root is of lesser value, and everything to the right of root is of greater 
//value. Public methods serve as a call to the actual private recursive method. 
#include "BSTree.h"

/****************************************************************************************************/
//											NODE
//===================================================================================================

//Default constructor
node::node()
{
	data = -1;
	left = NULL;
	right = NULL;
}

//Parameterized constructor
node::node(int x)
{
	data = x;
	left = NULL;
	right = NULL;
}
/****************************************************************************************************/

/****************************************************************************************************/
//											PRIVATE METHODS
//===================================================================================================

/**
* @FunctionName: count
* @Description:
*    Counts number of nodes
* @Params:
*    node *root - node pointer to the root of BST
* @Returns:
*    int - number of nodes
*/
int BSTree::count(node *root)
{
	if (!root)
	{
		return 0;
	}
	else
	{
		return 1 + count(root->left) + count(root->right);
	}
}
/**
* @FunctionName: insert
* @Description:
*    Recursively inserts node in tree depending on its value
*	 in respect to the root
* @Params:
*    node *root - node pointer to the root of BST
*    node *&temp - address of node to be inserted
* @Returns:
*    void
*/
void BSTree::insert(node *&root, node *&temp)
{
	if (!root)
	{
		root = temp;
	}
	else
	{
		if (temp->data < root->data)
		{
			insert(root->left, temp);
		}
		else
		{
			insert(root->right, temp);
		}
	}
}

/**
* @FunctionName: print_node
* @Description:
*	 Prints address,data, and label for the root and its children
* @Params:
*    node *root - pointer to root node
* @Returns:
*    node* - pointer to successor
*/
void BSTree::print_node(node *n, string label = "")
{
	if (label != "")
	{
		cout << "[" << label << "]";
	}
	cout << "[[" << n << "][" << n->data << "]]\n";
	if (n->left)
	{
		cout << "\t|-->[L][[" << n->left << "][" << n->left->data << "]]\n";
	}
	else
	{
		cout << "\t\\-->[L][null]\n";
	}
	if (n->right)
	{
		cout << "\t\\-->[R][[" << n->right << "][" << n->right->data << "]]\n";
	}
	else
	{
		cout << "\t\\-->[R][null]\n";
	}
}

/**
* @FunctionName: minValueNode
* @Description:
*	 Finds the smallest value in right subtree.
*	 If there is no right subtree, finds largest value in left subtree
* @Params:
*    node *root - pointer to root node
* @Returns:
*    node* - pointer to successor
*/
node* BSTree::minValueNode(node *root)
{
	node *current = root;

	if (root->right)
	{
		current = root->right;
		while (current->left != NULL)
		{
			current = current->left;
		}
	}
	else if (root->left)
	{
		current = root->left;
		while (current->right != NULL)
		{
			current = current->right;
		}
	}

	return current;
}

/**
* @FunctionName: deleteNode
* @Description:
*	 Finds node to be deleted.
*	 case 1: If no children, node is deleted
*	 case 2: If 1 child, node is bypassed
*	 case 3: If 2 children, root is swapped with successor and then deleted
* @Params:
*    node *&root - address of root node
*	 int key - data of node to be deleted
* @Returns:
*    node* - pointer to node that was deleted
*/
node* BSTree::deleteNode(node *&root, int key)
{
	if (!root)
	{
		return NULL;
	}
	if (key < root->data)
	{
		cout << "going left" << endl;
		root->left = deleteNode(root->left, key);
	}
	else if (key > root->data)
	{
		cout << "going right" << endl;
		root->right = deleteNode(root->right, key);
	}
	else
	{
		
		if (root->left == NULL)
		{
			node *temp = root->right;
			delete root;
			root = temp;			
			return temp;
		}
		else if (root->right == NULL)
		{
			
			node *temp = root->left;
			delete root;
			root = temp;
			return temp;
		}

		// node with two children: Get the inorder successor (smallest
		// in the right subtree)
		node *temp = minValueNode(root);

		print_node(temp, "minvaluenode");

		// Copy the inorder successor's content to this node
		root->data = temp->data;

		// Delete the inorder successor
		root->right = deleteNode(root->right, temp->data);
	}
	return root;
}

/**
* @FunctionName: height
* @Description:
*	 Compares height of left and right subtree,
*	 and returns the larger of the two
* @Params:
*    node *root - node pointer to root
* @Returns:
*    int - height of BST
*/
int BSTree::height(node *root)
{
	if (!root)
	{
		return 0;
	}
	else
	{
		int left = height(root->left);
		int right = height(root->right);
		if (left > right)
		{
			return left + 1;
		}
		else
		{
			return right + 1;
		}
	}
}


/**
* @FunctionName: printGivenLevel
* @Description:
*	 Print nodes at a given level
* @Params:
*    node *root - node pointer to root
*    int level - Level to print
* @Returns:
*    void
*/
void BSTree::printGivenLevel(node *root, int level)
{
	if (root == NULL)
		return;
	if (level == 1)
	{
		print_node(root);
	}
	else if (level > 1)
	{
		printGivenLevel(root->left, level - 1);
		printGivenLevel(root->right, level - 1);
	}
}

/**
* @FunctionName: GraphVizGetIds
* @Description:
*	 Method to help create GraphViz code so the expression tree can
*    be visualized. This method prints out all the unique node id's
*    by traversing the tree.
*	 Recivies a node pointer to root and performs a simple recursive
*	 tree traversal.
* @Params:
*    node *nodePtr - node pointer to root
*    ofstream &VizOut - allows writing to file
* @Returns:
*    void
*/
void BSTree::GraphVizGetIds(node *nodePtr, ofstream &VizOut)
{
	static int NullCount = 0;
	if (nodePtr)
	{
		GraphVizGetIds(nodePtr->left, VizOut);
		VizOut << "node" << nodePtr->data
			<< "[label=\"" << nodePtr->data << "\\n"
			//<<"Add:"<<nodePtr<<"\\n"
			//<<"Par:"<<nodePtr->parent<<"\\n"
			//<<"Rt:"<<nodePtr->right<<"\\n"
			//<<"Lt:"<<nodePtr->left<<"\\n"
			<< "\"]" << endl;
		if (!nodePtr->left)
		{
			NullCount++;
			VizOut << "nnode" << NullCount << "[label=\"X\",shape=point,width=.15]" << endl;
		}
		GraphVizGetIds(nodePtr->right, VizOut);
		if (!nodePtr->right)
		{
			NullCount++;
			VizOut << "nnode" << NullCount << "[label=\"X\",shape=point,width=.15]" << endl;
		}
	}
}

/**
* @FunctionName: GraphVizMakeConnections
* @Description:
*	 This method is partnered with the above method, but on this pass it
*    writes out the actual data from each node.
*    Don't worry about what this method and the above method do, just
*    use the output as your told:)
* @Params:
*    node *nodePtr - node pointer to root
*    ofstream &VizOut - allows writing to file
* @Returns:
*    void
*/
void BSTree::GraphVizMakeConnections(node *nodePtr, ofstream &VizOut)
{
	static int NullCount = 0;
	if (nodePtr)
	{
		GraphVizMakeConnections(nodePtr->left, VizOut);
		if (nodePtr->left)
			VizOut << "node" << nodePtr->data << "->"
			<< "node" << nodePtr->left->data << endl;
		else
		{
			NullCount++;
			VizOut << "node" << nodePtr->data << "->"
				<< "nnode" << NullCount << endl;
		}

		if (nodePtr->right)
			VizOut << "node" << nodePtr->data << "->"
			<< "node" << nodePtr->right->data << endl;
		else
		{
			NullCount++;
			VizOut << "node" << nodePtr->data << "->"
				<< "nnode" << NullCount << endl;
		}

		GraphVizMakeConnections(nodePtr->right, VizOut);
	}
}
/****************************************************************************************************/


/****************************************************************************************************/
//										PUBLIC METHODS
//===================================================================================================

//Default constructor
BSTree::BSTree()
{
	root = NULL;
}

//Destructor
BSTree::~BSTree()
{
}

/**
* @FunctionName: count
* @Description:
*    Counts number of nodes in tree
* @Params:
*    none
* @Returns:
*    int - number of nodes in BST
*/
int BSTree::count()
{
	return count(root);
}

/**
* @FunctionName: insert
* @Description:
*    inserts node into BST
* @Params:
*    int x - data of node
* @Returns:
*    void
*/
void BSTree::insert(int x)
{
	node *temp = new node(x);
	insert(root, temp);
}

/**
* @FunctionName: deleteNode
* @Description:
*    deletes a specific node
* @Params:
*    int key - data of node to be deleted
* @Returns:
*    void
*/
void BSTree::deleteNode(int key)
{
	deleteNode(root, key);
}

/**
* @FunctionName: minValue
* @Description:
*    prints the successor
* @Params:
*    none
* @Returns:
*    void
*/
void BSTree::minValue()
{
	print_node(minValueNode(root), "minVal");
}

/**
* @FunctionName: height
* @Description:
*    Returns height of tree
* @Params:
*    int key - default number -1
* @Returns:
*    int - height of tree
*/
int BSTree::height(int key = -1)
{
	if (key > 0)
	{
		//find node
	}
	else
	{
		return height(root);
	}
	return 0;
}

/**
* @FunctionName: top
* @Description:
*    Returns the data of root node
* @Params:
*    none
* @Returns:
*    int - data of root
*/
int BSTree::top()
{
	if (root)
		return root->data;
	else
		return 0;
}

/**
* @FunctionName: printLevelOrder
* @Description:
*    Function to line by line print level order traversal a tree
* @Params:
*    none
* @Returns:
*    void
*/
void BSTree::printLevelOrder()
{
	cout << "Begin Level Order===================\n";
	int h = height(root);
	int i;
	for (i = 1; i <= h; i++)
	{
		printGivenLevel(root, i);
		cout << "\n";
	}
	cout << "End Level Order===================\n";
}


/**
* @FunctionName: GraphVizOut
* @Description:
*    Recieves a filename to place the GraphViz data into.
*	 It then calls the above two graphviz methods to create a data file
*	 that can be used to visualize your expression tree.
* @Params:
*    string filename - name of file to write to
* @Returns:
*    int - number of nodes
*/
void BSTree::GraphVizOut(string filename)
{
	ofstream VizOut;
	VizOut.open(filename);
	VizOut << "Digraph G {\n";
	GraphVizGetIds(root, VizOut);
	GraphVizMakeConnections(root, VizOut);
	VizOut << "}\n";
	VizOut.close();
}
/****************************************************************************************************/
